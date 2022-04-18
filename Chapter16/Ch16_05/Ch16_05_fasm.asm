;-------------------------------------------------
;               Ch16_05_fasm.asm
;-------------------------------------------------

            include <MacrosX86-64-AVX.asmh>

;------------------------------------------------------------------------------
; extern "C" void Convolve1D_F32_Aavx2(float* y, const float* x, const float* kernel,
;   size_t num_pts, size_t kernel_size);
;------------------------------------------------------------------------------

NSE     equ     8                                   ;num_simd_elements
NSE2    equ     4                                   ;num_simd_elements2

        .code
Convolve1D_F32_Aavx2 proc frame
        CreateFrame_M CV_,0,0,rbx,rsi,r12,r13,r14
        EndProlog_M

; Validate arguments
        mov r10,qword ptr [rbp+CV_OffsetStackArgs]  ;r10 = kernel_size (ks)
        test r10,1
        jz Done                                 ;jump if ks is even
        cmp r10,3
        jb Done                                 ;jump if ks < 3
        cmp r9,r10
        jb Done                                 ;jump if num_pts < ks

; Initialize
        mov r11,r10                             ;r11 = ks
        shr r11,1                               ;r11 = ks2
        mov rsi,r9                              ;rsi = num_pts
        sub rsi,r11                             ;rsi = num_pts - ks2
        mov r14,r11
        neg r14                                 ;r14 = -ks2
        mov rax,r11                             ;i = ks2

; General-purpose registers used in code below
;   rax     i                   r9      num_pts
;   rbx     k                   r10     kernel_size
;   rcx     y array             r11     ks2
;   rdx     x array             r12     scratch
;   rsi     num_pts - ks2       r13     scratch
;   r8      kernel              r14     -ks2

; Loop1 is outer-most for-loop
        align 16
Loop1:  cmp rax,rsi
        jge Done                                ;jump if i >= num_pts - ks2

        lea r12,[rax+NSE]                       ;r12 = i + NSE
        cmp r12,rsi
        jg @F                                   ;jump if i + NSE > num_pts - ks2

        vxorps ymm0,ymm0,ymm0                   ;y[i:i+7] = 0
        mov rbx,r14                             ;k = -ks2

; Calculate y[i:i+7]
        align 16
Loop2a: mov r12,rax                             ;r12 = i
        sub r12,rbx                             ;r12 = i - k
        lea r13,[rbx+r11]                       ;r13 = k + ks2

        vbroadcastss ymm2,real4 ptr [r8+r13*4]          ;ymm2 = kernel[k+ks2]
        vfmadd231ps ymm0,ymm2,ymmword ptr [rdx+r12*4]   ;update y[i:i+7]

        inc rbx                                 ;k += 1
        cmp rbx,r11
        jle Loop2a                              ;jump if k <= ks2

        vmovups ymmword ptr [rcx+rax*4],ymm0    ;save y[i:i+7]
        add rax,NSE                             ;i += NSE
        jmp Loop1

@@:     lea r12,[rax+NSE2]                      ;r12 = i + NSE2
        cmp r12,rsi
        jg @F                                   ;jump if i + NSE2 > num_pts - ks2

        vxorps xmm0,xmm0,xmm0                   ;y[i:i+3] = 0
        mov rbx,r14                             ;k = -ks2

; Calculate y[i:i+3]
        align 16
Loop2b: mov r12,rax                             ;r12 = i
        sub r12,rbx                             ;r12 = i - k
        lea r13,[rbx+r11]                       ;r13 = k + ks2

        vbroadcastss xmm2,real4 ptr [r8+r13*4]          ;xmm2 = kernel[k+ks2]
        vfmadd231ps xmm0,xmm2,xmmword ptr [rdx+r12*4]   ;update y[i:i+3]

        inc rbx                                 ;k += 1
        cmp rbx,r11
        jle Loop2b                              ;jump if k <= ks2

        vmovups xmmword ptr [rcx+rax*4],xmm0    ;save y[i:i+3]
        add rax,NSE2                            ;i += NSE2
        jmp Loop1

@@:     vxorps xmm0,xmm0,xmm0                   ;y[i] = 0
        mov rbx,r14                             ;k = -ks2

; Calculate y[i]
        align 16
Loop2c: mov r12,rax                             ;r12 = i
        sub r12,rbx                             ;r12 = i - k
        lea r13,[rbx+r11]                       ;r13 = k + ks2

        vmovss xmm2,real4 ptr [r8+r13*4]            ;xmm2 = kernel[k+ks2]
        vfmadd231ss xmm0,xmm2,real4 ptr [rdx+r12*4] ;update y[i]

        inc rbx                                 ;k += 1
        cmp rbx,r11
        jle Loop2c                              ;jump if k <= ks2

        vmovss real4 ptr [rcx+rax*4],xmm0       ;save y[i]
        inc rax                                 ;i += 1
        jmp Loop1

Done:   vzeroupper
        DeleteFrame_M rbx,rsi,r12,r13,r14
        ret
Convolve1D_F32_Aavx2 endp

;------------------------------------------------------------------------------
; extern "C" void Convolve1DKs5_F32_Aavx2(float* y, const float* x,
;   const float* kernel, size_t num_pts);
;------------------------------------------------------------------------------

KS      equ     5                               ;kernel_size
KS2     equ     2                               ;floor(kernel_size / 2)

Convolve1DKs5_F32_Aavx2 proc frame
        CreateFrame_M CV5_,0,16,r12
        SaveXmmRegs_M xmm6
        EndProlog_M

; Validate arguments
        cmp r9,KS
        jb Done                                 ;jump if num_pts < KS

; Initialize
        mov rax,KS2                             ;i = ks2
        mov r10,r9                              ;r10 = num_pts
        sub r10,KS2                             ;r10 = num_pts - KS2

        vbroadcastss ymm0,real4 ptr [r8]        ;ymm0 = packed kernel[0]
        vbroadcastss ymm1,real4 ptr [r8+4]      ;ymm1 = packed kernel[1]
        vbroadcastss ymm2,real4 ptr [r8+8]      ;ymm2 = packed kernel[2]
        vbroadcastss ymm3,real4 ptr [r8+12]     ;ymm3 = packed kernel[3]
        vbroadcastss ymm4,real4 ptr [r8+16]     ;ymm4 = packed kernel[4]

; General-purpose registers used in code below
;   rax     i                   r9      num_pts
;   rcx     y array             r10     num_pts -= ks2
;   rdx     x array             r11     j
;   r8      kernel              r12     scratch

        align 16
Loop1:  cmp rax,r10
        jge Done                                ;jump if i >= num_pts - ks2

        lea r11,[rax+KS2]                       ;j = i + KS2
        lea r12,[rax+NSE]                       ;r12 = i + NSE
        cmp r12,r10
        jg @F                                   ;jump if i + NSE > num_pts - ks2

; Calculate y[i:i+7]
        vmulps ymm6,ymm0,ymmword ptr [rdx+r11*4]            ;kernel[0] * x[j]
        vfmadd231ps ymm6,ymm1,ymmword ptr [rdx+r11*4-4]     ;kernel[1] * x[j-1]
        vfmadd231ps ymm6,ymm2,ymmword ptr [rdx+r11*4-8]     ;kernel[2] * x[j-2]
        vfmadd231ps ymm6,ymm3,ymmword ptr [rdx+r11*4-12]    ;kernel[3] * x[j-3]
        vfmadd231ps ymm6,ymm4,ymmword ptr [rdx+r11*4-16]    ;kernel[4] * x[j-4]

        vmovups ymmword ptr [rcx+rax*4],ymm6                ;save y[i:i+7]
        add rax,NSE                                         ;i += NSE
        jmp Loop1

; Calculate y[i:i+3]
@@:     lea r12,[rax+NSE2]                      ;r12 = i + NSE2
        cmp r12,r10
        jg @F                                   ;jump if i + NSE2 > num_pts - ks2

        vmulps xmm6,xmm0,xmmword ptr [rdx+r11*4]            ;kernel[0] * x[j]
        vfmadd231ps xmm6,xmm1,xmmword ptr [rdx+r11*4-4]     ;kernel[1] * x[j-1]
        vfmadd231ps xmm6,xmm2,xmmword ptr [rdx+r11*4-8]     ;kernel[2] * x[j-2]
        vfmadd231ps xmm6,xmm3,xmmword ptr [rdx+r11*4-12]    ;kernel[3] * x[j-3]
        vfmadd231ps xmm6,xmm4,xmmword ptr [rdx+r11*4-16]    ;kernel[4] * x[j-4]

        vmovups xmmword ptr [rcx+rax*4],xmm6                ;save y[i:i+3]
        add rax,NSE2                                        ;i += NSE2
        jmp Loop1

; Calculate y[i]
@@:     vmulss xmm6,xmm0,real4 ptr [rdx+r11*4]              ;kernel[0] * x[j]
        vfmadd231ss xmm6,xmm1,real4 ptr [rdx+r11*4-4]       ;kernel[1] * x[j-1]
        vfmadd231ss xmm6,xmm2,real4 ptr [rdx+r11*4-8]       ;kernel[2] * x[j-2]
        vfmadd231ss xmm6,xmm3,real4 ptr [rdx+r11*4-12]      ;kernel[3] * x[j-3]
        vfmadd231ss xmm6,xmm4,real4 ptr [rdx+r11*4-16]      ;kernel[4] * x[j-4]
     
        vmovss real4 ptr [rcx+rax*4],xmm6                   ;save y[i]
        inc rax                                             ;i += 1
        jmp Loop1
        
Done:   vzeroupper
        RestoreXmmRegs_M xmm6
        DeleteFrame_M r12
        ret
Convolve1DKs5_F32_Aavx2 endp
        end
