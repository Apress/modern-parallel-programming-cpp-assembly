;-------------------------------------------------
;               Ch12_09_fasm.asm
;-------------------------------------------------

        include <MacrosX86-64-AVX.asmh>

;------------------------------------------------------------------------------
; extern "C" bool CalcBSA_Aavx(const double* ht, const double* wt, int n,
;   double* bsa1, double* bsa2, double* bsa3);
;------------------------------------------------------------------------------

                .const
r8_0p007184     real8 0.007184
r8_0p725        real8 0.725
r8_0p425        real8 0.425
r8_0p0235       real8 0.0235
r8_0p42246      real8 0.42246
r8_0p51456      real8 0.51456
r8_3600p0       real8 3600.0

        .code
        extern pow:proc

CalcBSA_Aavx proc frame
        CreateFrame_M BSA_,16,64,rbx,rsi,r12,r13,r14,r15
        SaveXmmRegs_M xmm6,xmm7,xmm8,xmm9
        EndProlog_M

; Save argument registers to home area (optional). Note that the home
; area can also be used to store other transient data values.
        mov qword ptr [rbp+BSA_OffsetHomeRCX],rcx
        mov qword ptr [rbp+BSA_OffsetHomeRDX],rdx
        mov qword ptr [rbp+BSA_OffsetHomeR8],r8
        mov qword ptr [rbp+BSA_OffsetHomeR9],r9

; Initialize processing loop pointers. Note that the pointers are
; maintained in non-volatile registers, which eliminates reloads after
; the calls to pow().
        test r8d,r8d                            ;is n > 0?
        jg @F                                   ;jump if n > 0

        xor eax,eax                             ;set error return code
        jmp Done

@@:     mov [rbp],r8d                           ;save n to local var
        mov r12,rcx                             ;r12 = ptr to ht
        mov r13,rdx                             ;r13 = ptr to wt
        mov r14,r9                              ;r14 = ptr to bsa1
        mov r15,[rbp+BSA_OffsetStackArgs]       ;r15 = ptr to bsa2
        mov rbx,[rbp+BSA_OffsetStackArgs+8]     ;rbx = ptr to bsa3
        mov rsi,-8                              ;rsi = array element offset

; Allocate home space on stack for use by pow()
        sub rsp,32

; Calculate bsa1 = 0.007184 * pow(ht, 0.725) * pow(wt, 0.425);
@@:     add rsi,8                                   ;rsi = next offset
        vmovsd xmm0,real8 ptr [r12+rsi]             ;xmm0 = ht
        vmovsd xmm8,xmm8,xmm0
        vmovsd xmm1,real8 ptr [r8_0p725]
        call pow                                    ;xmm0 = pow(ht, 0.725)
        vmovsd xmm6,xmm6,xmm0

        vmovsd xmm0,real8 ptr [r13+rsi]             ;xmm0 = wt
        vmovsd xmm9,xmm9,xmm0
        vmovsd xmm1,real8 ptr [r8_0p425]
        call pow                                    ;xmm0 = pow(wt, 0.425)
        vmulsd xmm6,xmm6,real8 ptr [r8_0p007184]
        vmulsd xmm6,xmm6,xmm0                       ;xmm6 = bsa1

; Calculate bsa2 = 0.0235 * pow(ht, 0.42246) * pow(wt, 0.51456);
        vmovsd xmm0,xmm0,xmm8                       ;xmm0 = ht
        vmovsd xmm1,real8 ptr [r8_0p42246]
        call pow                                    ;xmm0 = pow(ht, 0.42246)
        vmovsd xmm7,xmm7,xmm0

        vmovsd xmm0,xmm0,xmm9                       ;xmm0 = wt
        vmovsd xmm1,real8 ptr [r8_0p51456]
        call pow                                    ;xmm0 = pow(wt, 0.51456)
        vmulsd xmm7,xmm7,real8 ptr [r8_0p0235]
        vmulsd xmm7,xmm7,xmm0                       ;xmm7 = bsa2

; Calculate bsa3 = sqrt(ht * wt / 3600.0);
        vmulsd xmm8,xmm8,xmm9                   ;xmm8 = ht * wt
        vdivsd xmm8,xmm8,real8 ptr [r8_3600p0]  ;xmm8 = ht * wt / 3600
        vsqrtsd xmm8,xmm8,xmm8                  ;xmm8 = bsa3

; Save BSA results
        vmovsd real8 ptr [r14+rsi],xmm6         ;save bsa1 result
        vmovsd real8 ptr [r15+rsi],xmm7         ;save bsa2 result
        vmovsd real8 ptr [rbx+rsi],xmm8         ;save bsa3 result

        dec dword ptr [rbp]                     ;n -= 1
        jnz @B
        mov eax,1                               ;set success return code

Done:   RestoreXmmRegs_M xmm6,xmm7,xmm8,xmm9
        DeleteFrame_M rbx,rsi,r12,r13,r14,r15
        ret

CalcBSA_Aavx endp
        end
