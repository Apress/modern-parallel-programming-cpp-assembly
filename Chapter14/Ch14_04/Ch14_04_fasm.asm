;-------------------------------------------------
;               Ch14_04_fasm.asm
;-------------------------------------------------

            include <cmpequ.asmh>
            include <MacrosX86-64-AVX.asmh>

; The members of PA below must match the PA structure
; that's declared in Ch14_04.h

PA          struct
X1          qword ?
Y1          qword ?
X2          qword ?
Y2          qword ?
Dist1       qword ?
Dist2       qword ?
DistCmp1    qword ?
DistCmp2    qword ?
NumPoints   qword ?
PA          ends

NSE         equ 4                           ;num_simd_elements

            .const
r8_minus2   real8 -2.0

;------------------------------------------------------------------------------
; extern "C" bool CalcDistancesF64_Aavx(PA& pa);
;------------------------------------------------------------------------------

        extrn CheckArgs:proc

        .code
CalcDistancesF64_Aavx proc frame
        CreateFrame_M CDIS_,0,0,r12,r13
        EndProlog_M

; Make sure all PA pointers are properly aligned
        mov r12,rcx                             ;save pa
        sub rsp,32                              ;allocate home area for CheckArgs
        call CheckArgs                          ;validate pointers in pa
        or eax,eax
        jz Error                                ;jump if CheckArgs failed

; Initialize
        mov rdx,qword ptr [r12+PA.NumPoints]    ;rdx = NumPoints

        mov r8,qword ptr  [r12+PA.X1]           ;r8 = X1 array pointer
        mov r9,qword ptr  [r12+PA.X2]           ;r9 = X2 array pointer
        mov r10,qword ptr [r12+PA.Y1]           ;r10 = Y1 array pointer
        mov r11,qword ptr [r12+PA.Y2]           ;r11 = Y2 array pointer
        mov r12,qword ptr [r12+PA.Dist2]        ;r12 = Dist2 array pointer

        mov rax,-NSE                            ;initialize i

; Calculate distances using packed arithmetic
Loop1:  add rax,NSE                             ;i += NSE
        mov r13,rdx                             ;r13 = NumPoints
        sub r13,rax                             ;r13 = NumPoints - i
        cmp r13,NSE                             ;is NumPoints - i >= NSE?
        jb Loop2                                ;jump if no

        vmovdqa ymm0,ymmword ptr [r8+rax*8]      ;X1 vals
        vsubpd ymm0,ymm0,ymmword ptr [r9+rax*8]  ;X1[i:i+3] - X2[i:i+3]
        vmulpd ymm0,ymm0,ymm0                    ;calc squares
        
        vmovdqa ymm1,ymmword ptr [r10+rax*8]     ;Y1 vals
        vsubpd ymm1,ymm1,ymmword ptr [r11+rax*8] ;Y1[i:i+3] - Y2[i:i+3]
        vmulpd ymm1,ymm1,ymm1                    ;calc squares

        vaddpd ymm2,ymm0,ymm1                    ;packed sum of squares
        vsqrtpd ymm3,ymm2                        ;packed distances
        vmovdqa ymmword ptr [r12+rax*8],ymm3     ;save to Dist2[i:i+3]
        jmp Loop1

; Calculate distances for final few points
Loop2:  cmp rax,rdx                             ;is i >= n
        jae Done                                ;jump if yes

        vmovsd xmm0,real8 ptr [r8+rax*8]        ;xmm0 = X1[i]
        vsubsd xmm0,xmm0,real8 ptr [r9+rax*8]   ;xmm0 = X1[i] - X2[i]
        vmulsd xmm0,xmm0,xmm0                   ;xmm0 = (X1[i] - X2[i]) ** 2

        vmovsd xmm1,real8 ptr [r10+rax*8]       ;xmm1 = Y1[i]
        vsubsd xmm1,xmm1,real8 ptr [r11+rax*8]  ;xmm1 = Y1[i] - Y2[i]
        vmulsd xmm1,xmm1,xmm1                   ;xmm1 = (Y1[i] - Y2[i]) ** 2

        vaddsd xmm2,xmm0,xmm1                   ;sum of squares 
        vsqrtsd xmm3,xmm3,xmm2                  ;distance
        vmovsd real8 ptr[r12+rax*8],xmm3        ;save to Dist2[i]
        inc rax                                 ;i += 1
        jmp Loop2

Done:   mov eax,1                               ;set success return code
        vzeroupper

@@::    DeleteFrame_M r12,r13
        ret

Error:  xor eax,eax                             ;set errror return code
        jmp @B

CalcDistancesF64_Aavx endp

;------------------------------------------------------------------------------
; extern "C" void CompareDistancesF64_Aavx(PA& pa, const double* cmp_val);
;------------------------------------------------------------------------------

CompareDistancesF64_Aavx proc frame
        CreateFrame_M CD_,0,32
        SaveXmmRegs_M xmm6,xmm7
        EndProlog_M

; Initalize
        vbroadcastsd ymm6,real8 ptr [rdx]       ;packed cmp_val
        vbroadcastsd ymm7,real8 ptr [r8_minus2] ;packed -2.0

        mov r8,qword ptr [rcx+PA.Dist2]         ;r8 = Dist2 array pointer
        mov r9,qword ptr [rcx+PA.DistCmp2]      ;r9 = DistCmp2 array pointer
        mov r10,qword ptr [rcx+PA.NumPoints]    ;r10 = NumPoints

        mov rax,-NSE                            ;initialize i

; Calculate DistCmp2 values
Loop1:  add rax,NSE                             ;i += NSE
        mov r11,r10                             ;r11 = NumPoints
        sub r11,rax                             ;r11 = NumPoints - i
        cmp r11,NSE                             ;is NumPoints - i >= NSE?
        jb Loop2                                ;jump if no

        vmovdqa ymm0,ymmword ptr [r8+rax*8]     ;ymm0 = Dist2[i:i+3]
        vcmppd ymm1,ymm0,ymm6,CMP_GE_OQ         ;compare Dist2[i:i+3] to cmp_val

        vandpd ymm2,ymm1,ymm7                   ;ymm2 = -2.0 or 0.0
        vmulpd ymm3,ymm2,ymm0                   ;ymm3 = -2.0 * Dist2[i] or 0.0
        vandnpd ymm4,ymm1,ymm0                  ;ymm4 = 0.0 or Dist2[i]
        vorpd ymm5,ymm3,ymm4                    ;ymm5 = final result

        vmovdqa ymmword ptr[r9+rax*8],ymm5      ;save DistCmp2[i:i+3]
        jmp Loop1

; Calculate DistCmp2 values for residual elements
Loop2:  cmp rax,r10                             ;is i >= n?
        jae Done                                ;jump if yes

        vmovsd xmm0,real8 ptr [r8+rax*8]        ;xmm0 = Dist2[i]
        vcmpsd xmm1,xmm0,xmm6,CMP_GE_OQ         ;compare Dist2[i] to cmp_val

        vandpd xmm2,xmm1,xmm7                   ;xmm2 = -2.0 or 0.0
        vmulsd xmm3,xmm2,xmm0                   ;xmm3 = -2.0 * Dist2[i] or 0.0
        vandnpd xmm4,xmm1,xmm0                  ;xmm4  = 0.0 or Dist2[i]
        vorpd xmm5,xmm3,xmm4                    ;xmm5 = final result

        vmovsd real8 ptr[r9+rax*8],xmm5         ;save DistCmp2[i]
        inc rax                                 ;i += 1
        jmp Loop2

Done:   vzeroupper
        RestoreXmmRegs_M xmm6,xmm7
        DeleteFrame_M
        ret

CompareDistancesF64_Aavx endp
        end
