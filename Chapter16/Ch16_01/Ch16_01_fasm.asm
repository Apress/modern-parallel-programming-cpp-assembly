;-------------------------------------------------
;               Ch16_01_fasm.asm
;-------------------------------------------------

        include <MacrosX86-64-AVX.asmh>

;------------------------------------------------------------------------------
; ReducePD_M macro
;
; Description:  This macro sums the double-precision elements in register YmmSrc.
;               The result is saved in register XmmDes.
;
; Notes:        Register number XmmTemp must be different than XmmDes and YmmSrc.
;               Register numbers XmmDes and YmmSrc can be the same.
;------------------------------------------------------------------------------

ReducePD_M macro XmmDes,YmmSrc,XmmTemp
        TempSS SUBSTR <YmmSrc>,2        ;<TempSS> = <YmmSrc> sans leading char
        XmmSrc CATSTR <x>,TempSS        ;<XmmSrc> = "x" + <TempSS>

        vextractf128 XmmTemp,YmmSrc,1   ;extract two high-order F64 values
        vaddpd XmmDes,XmmTemp,XmmSrc    ;reduce to two F64 values
        vhaddpd XmmDes,XmmDes,XmmDes    ;reduce to one F64 value
        endm

;------------------------------------------------------------------------------
; extern "C" void CalcLeastSquares_Aavx2(double* m, double* b, const double* x,
;   const double* y, size_t n);
;------------------------------------------------------------------------------

NSE     equ 4                               ;num_simd_elements
        extern g_LsEpsilon:real8

        .code
CalcLeastSquares_Aavx2 proc frame
        CreateFrame_M LS_,0,64
        SaveXmmRegs_M xmm12,xmm13,xmm14,xmm15
        EndProlog_M

; Set m and b to zero (error values)
        xor eax,eax
        mov qword ptr [rcx],rax             ;m = 0
        mov qword ptr [rdx],rax             ;b = 0

; Validate arguments
        mov r10,qword ptr [rbp+LS_OffsetStackArgs]  ;r10 = n
        cmp r10,2
        jl Done                             ;jump if n < 2

        test r8,1fh
        jnz Done                            ;jump if x not 32b aligned
        test r9,1fh
        jnz Done                            ;jump if y not 32b aligned

; Initialize
        mov rax,-NSE                        ;rax = i
        vxorpd ymm12,ymm12,ymm12            ;packed sum_x = 0
        vxorpd ymm13,ymm13,ymm13            ;packed sum_y = 0
        vxorpd ymm14,ymm14,ymm14            ;packed sum_xx = 0
        vxorpd ymm15,ymm15,ymm15            ;packed sum_xy = 0

; Main processing loop
Loop1:  add rax,NSE                         ;i += NSE
        mov r11,r10                         ;r11 = n
        sub r11,rax                         ;r11 = n - i
        cmp r11,NSE
        jb @F                               ;jump if n - i < NSE

        vmovapd ymm0,ymmword ptr [r8+rax*8] ;load x[i:i+3]
        vmovapd ymm1,ymmword ptr [r9+rax*8] ;load y[i:i+3]

        vaddpd ymm12,ymm12,ymm0             ;update packed sum_x
        vaddpd ymm13,ymm13,ymm1             ;update packed sum_y
        vfmadd231pd ymm14,ymm0,ymm0         ;update packed sum_xx
        vfmadd231pd ymm15,ymm0,ymm1         ;update packed_sum_xy
        jmp Loop1

; Reduce packed sums to scalars
@@:     ReducePD_M xmm12,ymm12,xmm0         ;xmm12 = sum_x
        ReducePD_M xmm13,ymm13,xmm0         ;xmm13 = sum_y
        ReducePD_M xmm14,ymm14,xmm0         ;xmm14 = sum_xx
        ReducePD_M xmm15,ymm15,xmm0         ;xmm15 = sum_xy

; Process any residual elements
Loop2:  cmp rax,r10
        jae CalcLS                          ;jump if i >= n

        vmovsd xmm0,real8 ptr [r8+rax*8]    ;load x[i]
        vmovsd xmm1,real8 ptr [r9+rax*8]    ;load y[i]

        vaddsd xmm12,xmm12,xmm0             ;update sum_x
        vaddsd xmm13,xmm13,xmm1             ;update sum_y
        vfmadd231sd xmm14,xmm0,xmm0         ;update sum_xx
        vfmadd231sd xmm15,xmm0,xmm1         ;update sum_xy

        inc rax                             ;i += 1
        jmp Loop2

CalcLS: vcvtsi2sd xmm5,xmm5,r10             ;xmm5 = n
        vmulsd xmm0,xmm5,xmm14              ;xmm0 = n * sum_xx
        vmulsd xmm1,xmm12,xmm12             ;xmm1 = sum_x * sum_x
        vsubsd xmm0,xmm0,xmm1               ;xmm0 = denom

        mov rax,7fffffffffffffffh           ;abs mask
        vmovq xmm1,rax
        vandpd xmm4,xmm0,xmm1               ;xmm4 = fabs(denom)
        vcomisd xmm4,[g_LsEpsilon]
        jb Done                             ;jump if denom < fabs(g_LsEpsilon)

; Compute and save slope
        vmulsd xmm0,xmm5,xmm15              ;n * sum_xy
        vmulsd xmm1,xmm12,xmm13             ;sum_x * sum_y
        vsubsd xmm2,xmm0,xmm1               ;n * sum_xy - sum_x * sum_y
        vdivsd xmm3,xmm2,xmm4               ;xmm3 = slope
        vmovsd real8 ptr [rcx],xmm3         ;save slope

; Compute and save intercept
        vmulsd xmm0,xmm14,xmm13             ;sum_xx * sum_y
        vmulsd xmm1,xmm12,xmm15             ;sum_x * sum_xy
        vsubsd xmm2,xmm0,xmm1               ;sum_xx * sum_y - sum_x _ sum_xy
        vdivsd xmm3,xmm2,xmm4               ;xmm3 = intercept
        vmovsd real8 ptr [rdx],xmm3         ;save intercept

Done:   vzeroupper
        RestoreXmmRegs_M xmm12,xmm13,xmm14,xmm15
        DeleteFrame_M
        ret
CalcLeastSquares_Aavx2 endp
        end
