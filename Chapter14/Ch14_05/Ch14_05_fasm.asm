;-------------------------------------------------
;               Ch14_05_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" void CalcColumnMeansF64_Aavx(double* col_means, const double* x,
;   size_t nrows, size_t ncols);
;------------------------------------------------------------------------------

NSE     equ 4                               ;num_simd_elements
NSE2    equ 2                               ;num_simd_elements2

        .code
CalcColumnMeansF64_Aavx proc frame

; Function prologue
        push rbx
        .pushreg rbx
        push rdi
        .pushreg rdi
        .endprolog

; Validate nrows and ncols
        test r8,r8
        jz Done                             ;jump if nrows == 0
        test r9,r9
        jz Done                             ;jump if ncols == 0

; Initialize all elements in col_means to 0.0
        mov r10,rcx                         ;save col_means for later
        mov rdi,rcx                         ;rdi = col_means
        mov rcx,r9                          ;number of elements in ncol_means
        xor eax,eax                         ;rax = fill value
        rep stosq                           ;fill col_means with 0

;   Register use in code below
;
;   rbx = &x[i][j]            r8  = nrows       rax = scratch register
;   rcx = &x[0][0]            r9  = ncols
;   rdx = &col_means[j]       r10 = i
;   rdi = &col_means[0]       r11 = j

; Initialize
        mov rcx,rdx                         ;rcx = &x[0][0]
        mov rdi,r10                         ;rdi = &col_means[0]
        xor r10d,r10d                       ;i = 0

; Repeat Loop1 while i < nrows
Loop1:  cmp r10,r8
        jae CalcCM                          ;jump if i >= nrows

        xor r11d,r11d                       ;j = 0

; Repeat Loop2 while j < ncols
Loop2:  cmp r11,r9
        jb @F                               ;jump if j < ncols

        inc r10                             ;i += 1
        jmp Loop1

; Calculate &x[i][j] and &col_means[j]
@@:     mov rax,r10                         ;rax = i
        mul r9                              ;rax = i * ncols
        add rax,r11                         ;rax = i * ncols + j
        lea rbx,[rcx+rax*8]                 ;rbx = &x[i][j]
        lea rdx,[rdi+r11*8]                 ;rdx = &col_means[j]

        mov rax,r11                         ;rax = j
        add rax,NSE                         ;rax = j + NSE
        cmp rax,r9
        ja @F                               ;jump if j + NSE > ncols

; Update sums (4 columns)
        vmovupd ymm0,ymmword ptr [rdx]      ;ymm0 = col_means[j:j+3]
        vaddpd ymm1,ymm0,ymmword ptr [rbx]  ;col_means[j:j+3] += x[i][j:j+3]
        vmovupd ymmword ptr [rdx],ymm1      ;save result

        add r11,NSE                         ;j += NSE
        jmp Loop2

@@:     mov rax,r11                         ;rax = j
        add rax,NSE2                        ;rax = j + NSE2
        cmp rax,r9
        ja @F                               ;jump if j + NSE2 > ncols

; Update sums (2 columns)
        vmovupd xmm0,xmmword ptr [rdx]      ;xmm0 = col_means[j:j+1]
        vaddpd xmm1,xmm0,xmmword ptr [rbx]  ;col_means[j:j+1] += x[i][j:j+1]
        vmovupd xmmword ptr [rdx],xmm1      ;save result

        add r11,NSE2                        ;j += NSE2
        jmp Loop2

; Update sums (1 column)
@@:     vmovsd xmm0,real8 ptr [rdx]         ;xmm0 = col_means[j]
        vaddsd xmm1,xmm0,real8 ptr [rbx]    ;col_means[j] += x[i][j]
        vmovsd real8 ptr [rdx],xmm1         ;save result

        inc r11                             ;j += 1
        jmp Loop2

; Calculate column means
CalcCM: xor eax,eax                         ;j = 0;
        vcvtsi2sd xmm2,xmm2,r8              ;xmm2 = nrows (DPFP)

Loop3:  vmovsd xmm0,real8 ptr [rdi+rax*8]   ;col_means[j]
        vdivsd xmm1,xmm0,xmm2               ;mean = col_means[j] / nrows
        vmovsd real8 ptr [rdi+rax*8],xmm1   ;save result

        inc rax                             ;j += 1
        cmp rax,r9
        jb Loop3                            ;jump if j < ncols

Done:   vzeroupper
        pop rdi
        pop rbx
        ret
CalcColumnMeansF64_Aavx endp
        end
