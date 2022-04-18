;-------------------------------------------------
;               Ch12_04_fasm.asm
;-------------------------------------------------

MxcsrRcMask     equ 9fffh                   ;bit mask for MXCSR.RC
MxcsrRcShift    equ 13                      ;shift count for MXCSR.RC

;------------------------------------------------------------------------------
; Macro GetRC_M - copies MXCSR.RC to r10d[1:0]
;------------------------------------------------------------------------------

GetRC_M macro
        vstmxcsr dword ptr [rsp+8]          ;save mxcsr register
        mov r10d,[rsp+8]

        shr r10d,MxcsrRcShift               ;r10d[1:0] = MXCSR.RC bits
        and r10d,3                          ;clear unused bits
        endm

;------------------------------------------------------------------------------
; Macro SetRC_M - sets MXCSR.RC to rm_reg[1:0]
;------------------------------------------------------------------------------

SetRC_M macro RcReg
        vstmxcsr dword ptr [rsp+8]          ;save current MXCSR
        mov eax,[rsp+8]

        and RcReg,3                         ;clear unusned bits
        shl RcReg,MxcsrRcShift              ;rc_reg[14:13] = rc

        and eax,MxcsrRcMask                 ;clear non MXCSR.RC bits
        or eax,RcReg                        ;insert new MXCSR.RC

        mov [rsp+8],eax
        vldmxcsr dword ptr [rsp+8]          ;load updated MXCSR
        endm

;------------------------------------------------------------------------------
; extern "C" bool ConvertScalar_Aavx(Uval* des, const Uval* src, CvtOp cvt_op, RC rc)
;
; Note:     This function requires linker option /LARGEADDRESSAWARE:NO
;------------------------------------------------------------------------------

        .code
ConvertScalar_Aavx proc

; Make sure cvt_op is valid
        cmp r8d,CvtOpTableCount             ;is cvt_op >= CvtOpTableCount
        jae BadCvtOp                        ;jump if cvt_op is invalid

; Save current MSCSR.RC
        GetRC_M                             ;r10d = current RC

; Set new rounding mode
        SetRC_M r9d                         ;set new MXCSR.RC

; Jump to target conversion code block
        mov eax,r8d                         ;rax = cvt_op
        jmp [CvtOpTable+rax*8]

; Conversions between int32_t and float/double

I32_F32:
        mov eax,[rdx]                       ;load integer value
        vcvtsi2ss xmm0,xmm0,eax             ;convert to float
        vmovss real4 ptr [rcx],xmm0         ;save result
        jmp Done

F32_I32:
        vmovss xmm0,real4 ptr [rdx]         ;load float value
        vcvtss2si eax,xmm0                  ;convert to integer
        mov [rcx],eax                       ;save result
        jmp Done

I32_F64:
        mov eax,[rdx]                       ;load integer value
        vcvtsi2sd xmm0,xmm0,eax             ;convert to double
        vmovsd real8 ptr [rcx],xmm0         ;save result
        jmp Done

F64_I32:
        vmovsd xmm0,real8 ptr [rdx]         ;load double value
        vcvtsd2si eax,xmm0                  ;convert to integer
        mov [rcx],eax                       ;save result
        jmp Done

; Conversions between int64_t and float/double

I64_F32:
        mov rax,[rdx]                       ;load integer value
        vcvtsi2ss xmm0,xmm0,rax             ;convert to float
        vmovss real4 ptr [rcx],xmm0         ;save result
        jmp Done

F32_I64:
        vmovss xmm0,real4 ptr [rdx]         ;load float value
        vcvtss2si rax,xmm0                  ;convert to integer
        mov [rcx],rax                       ;save result
        jmp Done

I64_F64:
        mov rax,[rdx]                       ;load integer value
        vcvtsi2sd xmm0,xmm0,rax             ;convert to double
        vmovsd real8 ptr [rcx],xmm0         ;save result
        jmp Done

F64_I64:
        vmovsd xmm0,real8 ptr [rdx]         ;load double value
        vcvtsd2si rax,xmm0                  ;convert to integer
        mov [rcx],rax                       ;save result
        jmp Done

; Conversions between float and double

F32_F64:
        vmovss xmm0,real4 ptr [rdx]         ;load float value
        vcvtss2sd xmm1,xmm1,xmm0            ;convert to double
        vmovsd real8 ptr [rcx],xmm1         ;save result
        jmp Done

F64_F32:
        vmovsd xmm0,real8 ptr [rdx]         ;load double value
        vcvtsd2ss xmm1,xmm1,xmm0            ;convert to float
        vmovss real4 ptr [rcx],xmm1         ;save result
        jmp Done

BadCvtOp:
        xor eax,eax                         ;set error return code
        ret

Done:   SetRC_M r10d                        ;restore original MXCSR.RC
        mov eax,1                           ;set success return code
        ret

; The order of values in following table must match enum CvtOp
; that's defined in the .h file.

        align 8
CvtOpTable equ $
        qword I32_F32, F32_I32
        qword I32_F64, F64_I32
        qword I64_F32, F32_I64
        qword I64_F64, F64_I64
        qword F32_F64, F64_F32
CvtOpTableCount equ ($ - CvtOpTable) / size qword

ConvertScalar_Aavx endp
        end
