;-------------------------------------------------
;               Ch18_06_fasm.asm
;-------------------------------------------------

            include <MacrosX86-64-AVX.asmh>

;------------------------------------------------------------------------------
; extern "C" void Convolve1D_F32_Aavx512(float* y, const float* x,
;   const float* kernel, size_t num_pts, size_t kernel_size);
;------------------------------------------------------------------------------

NSE     equ     16                              ;num F32 elements in ZMM register

        .code
Convolve1D_F32_Aavx512 proc frame
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

;------------------------------------------------------------------------------
; General-purpose registers used in code below
;   rax     i                   r9      num_pts
;   rbx     k                   r10     kernel_size
;   rcx     y array             r11     ks2
;   rdx     x array             r12     scratch
;   rsi     num_pts - ks2       r13     scratch
;   r8      kernel              r14     -ks2
;------------------------------------------------------------------------------

; Loop1 is outer-most for-loop
        align 16
Loop1:  cmp rax,rsi
        jge Done                                ;jump if i >= num_pts - ks2

; Calculate y[i:i+NSE*2-1]
        lea r12,[rax+NSE*2]                     ;r12 = i + NSE * 2
        cmp r12,rsi
        jg @F                                   ;jump if i + NSE * 2 > num_pts - ks2

        vxorps zmm0,zmm0,zmm0                   ;y[i:i+NSE-1] = 0
        vxorps zmm1,zmm1,zmm1                   ;y[i+NSE:i+NSE*2-1] = 0
        mov rbx,r14                             ;k = -ks2

        align 16
Loop2a: mov r12,rax                             ;r12 = i
        sub r12,rbx                             ;r12 = i - k
        lea r13,[rbx+r11]                       ;r13 = k + ks2

        vbroadcastss zmm5,real4 ptr [r8+r13*4]              ;zmm2 = kernel[k+ks2]
        vfmadd231ps zmm0,zmm5,zmmword ptr [rdx+r12*4]       ;update y[i:i+NSE-1]
        vfmadd231ps zmm1,zmm5,zmmword ptr [rdx+r12*4+64]    ;update y[i+NSE:i+NSE*2-1]

        inc rbx                                 ;k += 1
        cmp rbx,r11
        jle Loop2a                              ;jump if k <= ks2

        vmovups zmmword ptr [rcx+rax*4],zmm0        ;save y[i:i+NSE-1]
        vmovups zmmword ptr [rcx+rax*4+64],zmm1     ;save y[i+NSE:i+NSE*2-1]
        add rax,NSE*2                               ;i += NSE * 2
        jmp Loop1

; Calculate y[i:i+NSE-1]
@@:     lea r12,[rax+NSE]                       ;r12 = i + NSE
        cmp r12,rsi
        jg @F                                   ;jump if i + NSE > num_pts - ks2

        vxorps zmm0,zmm0,zmm0                   ;y[i:i+NSE-1] = 0
        mov rbx,r14                             ;k = -ks2

        align 16
Loop2b: mov r12,rax                             ;r12 = i
        sub r12,rbx                             ;r12 = i - k
        lea r13,[rbx+r11]                       ;r13 = k + ks2

        vbroadcastss zmm5,real4 ptr [r8+r13*4]          ;zmm2 = kernel[k+ks2]
        vfmadd231ps zmm0,zmm5,zmmword ptr [rdx+r12*4]   ;update y[i:i+NSE-1]

        inc rbx                                 ;k += 1
        cmp rbx,r11
        jle Loop2b                              ;jump if k <= ks2

        vmovups zmmword ptr [rcx+rax*4],zmm0    ;save y[i:i+NSE-1]
        add rax,NSE                             ;i += NSE
        jmp Loop1

; Calculate y[i:i+NSE/2-1]
@@:     lea r12,[rax+NSE/2]                     ;r12 = i + NSE / 2
        cmp r12,rsi
        jg @F                                   ;jump if i + NSE / 2 > num_pts - ks2

        vxorps ymm0,ymm0,ymm0                   ;y[i:i+NSE/2-1] = 0
        mov rbx,r14                             ;k = -ks2

        align 16
Loop2c: mov r12,rax                             ;r12 = i
        sub r12,rbx                             ;r12 = i - k
        lea r13,[rbx+r11]                       ;r13 = k + ks2

        vbroadcastss ymm5,real4 ptr [r8+r13*4]          ;ymm2 = kernel[k+ks2]
        vfmadd231ps ymm0,ymm5,ymmword ptr [rdx+r12*4]   ;update y[i:i+NSE/2-1]

        inc rbx                                 ;k += 1
        cmp rbx,r11
        jle Loop2c                              ;jump if k <= ks2

        vmovups ymmword ptr [rcx+rax*4],ymm0    ;save y[i:i+NSE/2-1]
        add rax,NSE/2                           ;i += NSE/2
        jmp Loop1

; Calculate y[i:i+NSE/4-1]
@@:     lea r12,[rax+NSE/4]                     ;r12 = i + NSE / 4
        cmp r12,rsi
        jg @F                                   ;jump if i + NSE / 4 > num_pts - ks2

        vxorps xmm0,xmm0,xmm0                   ;y[i:i+NSE/4-1] = 0
        mov rbx,r14                             ;k = -ks2

        align 16
Loop2d: mov r12,rax                             ;r12 = i
        sub r12,rbx                             ;r12 = i - k
        lea r13,[rbx+r11]                       ;r13 = k + ks2

        vbroadcastss xmm5,real4 ptr [r8+r13*4]          ;xmm2 = kernel[k+ks2]
        vfmadd231ps xmm0,xmm5,xmmword ptr [rdx+r12*4]   ;update y[i:i+NSE/4-1]

        inc rbx                                 ;k += 1
        cmp rbx,r11
        jle Loop2d                              ;jump if k <= ks2

        vmovups xmmword ptr [rcx+rax*4],xmm0    ;save y[i:i+NSE/4-1]
        add rax,NSE/4                           ;i += NSE / 4
        jmp Loop1

; Calculate y[i]
@@:     vxorps xmm0,xmm0,xmm0                   ;y[i] = 0
        mov rbx,r14                             ;k = -ks2

        align 16
Loop2e: mov r12,rax                             ;r12 = i
        sub r12,rbx                             ;r12 = i - k
        lea r13,[rbx+r11]                       ;r13 = k + ks2

        vmovss xmm5,real4 ptr [r8+r13*4]            ;xmm2 = kernel[k+ks2]
        vfmadd231ss xmm0,xmm5,real4 ptr [rdx+r12*4] ;update y[i]

        inc rbx                                 ;k += 1
        cmp rbx,r11
        jle Loop2e                              ;jump if k <= ks2

        vmovss real4 ptr [rcx+rax*4],xmm0       ;save y[i]
        inc rax                                 ;i += 1
        jmp Loop1

Done:   vzeroupper
        DeleteFrame_M rbx,rsi,r12,r13,r14
        ret
Convolve1D_F32_Aavx512 endp

;------------------------------------------------------------------------------
; extern "C" void Convolve1DKs5_F32_Aavx512(float* y, const float* x,
;   const float* kernel, size_t num_pts);
;------------------------------------------------------------------------------

KS      equ     5                               ;kernel_size
KS2     equ     2                               ;floor(kernel_size / 2)

Convolve1DKs5_F32_Aavx512 proc frame
        CreateFrame_M CV5_,0,0,r12
        EndProlog_M

; Validate arguments
        cmp r9,KS
        jb Done                                 ;jump if num_pts < KS

; Initialize
        mov rax,KS2                             ;i = ks2
        mov r10,r9                              ;r10 = num_pts
        sub r10,KS2                             ;r10 = num_pts - KS2

        vbroadcastss zmm0,real4 ptr [r8]        ;zmm0 = packed kernel[0]
        vbroadcastss zmm1,real4 ptr [r8+4]      ;zmm1 = packed kernel[1]
        vbroadcastss zmm2,real4 ptr [r8+8]      ;zmm2 = packed kernel[2]
        vbroadcastss zmm3,real4 ptr [r8+12]     ;zmm3 = packed kernel[3]
        vbroadcastss zmm4,real4 ptr [r8+16]     ;zmm4 = packed kernel[4]

;------------------------------------------------------------------------------
; General-purpose registers used in code below
;   rax     i                   r9      num_pts
;   rcx     y array             r10     num_pts - ks2
;   rdx     x array             r11     j
;   r8      kernel              r12     scratch
;------------------------------------------------------------------------------

        align 16
Loop1:  cmp rax,r10
        jge Done                                ;jump if i >= num_pts - ks2

; Calculate y[i:i+NSE*2-1]
        lea r11,[rax+KS2]                       ;j = i + KS2
        lea r12,[rax+NSE*2]                     ;r12 = i + NSE * 2
        cmp r12,r10
        jg @F                                   ;jump if i + NSE * 2 > num_pts - ks2

        vmulps zmm5,zmm0,zmmword ptr [rdx+r11*4]                ;kernel[0] * x[j]
        vfmadd231ps zmm5,zmm1,zmmword ptr [rdx+r11*4-4]         ;kernel[1] * x[j-1]
        vfmadd231ps zmm5,zmm2,zmmword ptr [rdx+r11*4-8]         ;kernel[2] * x[j-2]
        vfmadd231ps zmm5,zmm3,zmmword ptr [rdx+r11*4-12]        ;kernel[3] * x[j-3]
        vfmadd231ps zmm5,zmm4,zmmword ptr [rdx+r11*4-16]        ;kernel[4] * x[j-4]

        vmulps zmm16,zmm0,zmmword ptr [rdx+r11*4+64]            ;kernel[0] * x[j]
        vfmadd231ps zmm16,zmm1,zmmword ptr [rdx+r11*4-4+64]     ;kernel[1] * x[j-1]
        vfmadd231ps zmm16,zmm2,zmmword ptr [rdx+r11*4-8+64]     ;kernel[2] * x[j-2]
        vfmadd231ps zmm16,zmm3,zmmword ptr [rdx+r11*4-12+64]    ;kernel[3] * x[j-3]
        vfmadd231ps zmm16,zmm4,zmmword ptr [rdx+r11*4-16+64]    ;kernel[4] * x[j-4]

        vmovups zmmword ptr [rcx+rax*4],zmm5                ;save y[i:i+NSE-1]
        vmovups zmmword ptr [rcx+rax*4+64],zmm16            ;save y[i+NSE:i+NSE*2-1]
        add rax,NSE*2                                       ;i += NSE * 2
        jmp Loop1

; Calculate y[i:i+NSE-1]
        lea r11,[rax+KS2]                       ;j = i + KS2
        lea r12,[rax+NSE]                       ;r12 = i + NSE
        cmp r12,r10
        jg @F                                   ;jump if i + NSE > num_pts - ks2

        vmulps zmm5,zmm0,zmmword ptr [rdx+r11*4]            ;kernel[0] * x[j]
        vfmadd231ps zmm5,zmm1,zmmword ptr [rdx+r11*4-4]     ;kernel[1] * x[j-1]
        vfmadd231ps zmm5,zmm2,zmmword ptr [rdx+r11*4-8]     ;kernel[2] * x[j-2]
        vfmadd231ps zmm5,zmm3,zmmword ptr [rdx+r11*4-12]    ;kernel[3] * x[j-3]
        vfmadd231ps zmm5,zmm4,zmmword ptr [rdx+r11*4-16]    ;kernel[4] * x[j-4]

        vmovups zmmword ptr [rcx+rax*4],zmm5                ;save y[i:i+NSE-1]
        add rax,NSE                                         ;i += NSE
        jmp Loop1

; Calculate y[i:i+NSE/2-1]
@@:     lea r12,[rax+NSE/2]                     ;r12 = i + NSE / 2
        cmp r12,r10
        jg @F                                   ;jump if i + NSE / 2 > num_pts - ks2

        vmulps ymm5,ymm0,ymmword ptr [rdx+r11*4]            ;kernel[0] * x[j]
        vfmadd231ps ymm5,ymm1,ymmword ptr [rdx+r11*4-4]     ;kernel[1] * x[j-1]
        vfmadd231ps ymm5,ymm2,ymmword ptr [rdx+r11*4-8]     ;kernel[2] * x[j-2]
        vfmadd231ps ymm5,ymm3,ymmword ptr [rdx+r11*4-12]    ;kernel[3] * x[j-3]
        vfmadd231ps ymm5,ymm4,ymmword ptr [rdx+r11*4-16]    ;kernel[4] * x[j-4]

        vmovups ymmword ptr [rcx+rax*4],ymm5                ;save y[i:i+NSE/2-1]
        add rax,NSE/2                                       ;i += NSE/2
        jmp Loop1

; Calculate y[i:i+NSE/4-1]
@@:     lea r12,[rax+NSE/4]                     ;r12 = i + NSE / 4
        cmp r12,r10
        jg @F                                   ;jump if i + NSE / 4 > num_pts - ks2

        vmulps xmm5,xmm0,xmmword ptr [rdx+r11*4]            ;kernel[0] * x[j]
        vfmadd231ps xmm5,xmm1,xmmword ptr [rdx+r11*4-4]     ;kernel[1] * x[j-1]
        vfmadd231ps xmm5,xmm2,xmmword ptr [rdx+r11*4-8]     ;kernel[2] * x[j-2]
        vfmadd231ps xmm5,xmm3,xmmword ptr [rdx+r11*4-12]    ;kernel[3] * x[j-3]
        vfmadd231ps xmm5,xmm4,xmmword ptr [rdx+r11*4-16]    ;kernel[4] * x[j-4]

        vmovups xmmword ptr [rcx+rax*4],xmm5                ;save y[i:i+NSE/4-1]
        add rax,NSE/4                                       ;i += NSE / 4
        jmp Loop1

; Calculate y[i]
@@:     vmulss xmm5,xmm0,real4 ptr [rdx+r11*4]              ;kernel[0] * x[j]
        vfmadd231ss xmm5,xmm1,real4 ptr [rdx+r11*4-4]       ;kernel[1] * x[j-1]
        vfmadd231ss xmm5,xmm2,real4 ptr [rdx+r11*4-8]       ;kernel[2] * x[j-2]
        vfmadd231ss xmm5,xmm3,real4 ptr [rdx+r11*4-12]      ;kernel[3] * x[j-3]
        vfmadd231ss xmm5,xmm4,real4 ptr [rdx+r11*4-16]      ;kernel[4] * x[j-4]
     
        vmovss real4 ptr [rcx+rax*4],xmm5                   ;save y[i]
        inc rax                                             ;i += 1
        jmp Loop1
        
Done:   vzeroupper
        DeleteFrame_M r12
        ret
Convolve1DKs5_F32_Aavx512 endp
        end
