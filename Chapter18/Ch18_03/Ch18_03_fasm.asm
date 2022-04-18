;-------------------------------------------------
;               Ch18_03_fasm.asm
;-------------------------------------------------

        include <MacrosX86-64-AVX.asmh>

;------------------------------------------------------------------------------
; extern "C" void CalcCovMatF64_Aavx512(double* cov_mat, double* var_means,
;   const double* x, size_t n_vars, size_t n_obvs);
;------------------------------------------------------------------------------

NSE     equ     8                           ;num_simd_elements

        .code
CalcCovMatF64_Aavx512 proc frame
        CreateFrame_M COV_,0,0,rbx,r12,r13,r14,r15
        EndProlog_M

; Initialize
        mov r10,qword ptr [rbp+COV_OffsetStackArgs] ;r10 = n_obvs
        vcvtusi2sd xmm16,xmm16,r10                  ;convert n_obvs to F64
        mov rax,r10
        dec rax                                     ;rax = n_obvs - 1
        vcvtusi2sd xmm17,xmm17,rax                  ;convert n_obvs - 1 to F64
        mov rax,-1                                  ;rax = i

;----------------------------------------------------------------------
; Calculate var_means[i] (mean of row i in matrix x)
;
; General-purpose register use in code that calculates var_means[i]
;
;   rax     i                       r10     n_obvs 
;   rbx     j                       r11     scratch register
;   rcx     cov_mat                 r12     -----                 
;   rdx     var_means               r13     -----
;   r8      x                       r14     i * n_obvs
;   r9      n_vars                  r15     -----
;----------------------------------------------------------------------

        align 16
Loop1:  inc rax                             ;i += 1
        cmp rax,r9
        jae CalcCV                          ;jump if i >= n_vars

        mov r14,rax                         ;r14 = i
        imul r14,r10                        ;r14 = i * n_obvs
        mov rbx,-NSE                        ;rbx = j
        vxorpd zmm0,zmm0,zmm0               ;sums[0:7] = 0               

; Sum elements in row x[i]
        align 16
Loop2:  add rbx,NSE                         ;j += NSE
        mov r11,r10                         ;r11 = n_obvs
        sub r11,rbx                         ;r11 = n_obvs - j
        cmp r11,NSE
        jb @F                               ;jump if n_objs - j < NSE

        lea r11,[r14+rbx]                       ;r11 = i * n_obvs + j
        vaddpd zmm0,zmm0,zmmword ptr [r8+r11*8] ;sums[0:7] += x[i][j:j+NSE-1]
        jmp Loop2

; Update sums for row x[i] if 4 or more elements remain 
@@:     vextractf64x4 ymm1,zmm0,1           ;reduce sums (4 elements)
        vaddpd ymm0,ymm0,ymm1
        mov r11,r10                         ;r11 = n_obvs
        sub r11,rbx                         ;r11 = n_obvs - j
        cmp r11,NSE/2
        jb @F                               ;jump if n_objs - j < NSE / 2

        lea r11,[r14+rbx]                       ;r11 = i * n_obvs + j
        vaddpd ymm0,ymm0,ymmword ptr [r8+r11*8] ;sums[0:3] += x[i][j:j+NSE/2-1]
        add rbx,NSE/2                           ;j += NSE / 2

; Update sums for row x[i] if 2 or more elements remain 
@@:     vextractf64x2 xmm1,ymm0,1           ;reduce sums (2 elements)
        vaddpd xmm0,xmm0,xmm1
        mov r11,r10                         ;r11 = n_obvs
        sub r11,rbx                         ;r11 = n_obvs - j
        cmp r11,NSE/4
        jb @F                               ;jump if n_objs - j < NSE / 4

        lea r11,[r14+rbx]                       ;r11 = i * n_obvs + j
        vaddpd xmm0,xmm0,xmmword ptr [r8+r11*8] ;sums[0:1] += x[i][j:j+NSE/4-1]
        add rbx,NSE/4                           ;j += NSE / 4

; Update sums for row x[i] if 1 element remains 
@@:     vhaddpd xmm0,xmm0,xmm0              ;reduce sums (scalar element)
        cmp rbx,r10
        jae CalcM                           ;jump if j >= n_obvs

        lea r11,[r14+rbx]                       ;r11 = i * n_obvs + j
        vaddsd xmm0,xmm0,real8 ptr [r8+r11*8]   ;sum += x[i][j]

; Calculate var_means[i]
CalcM:  vdivsd xmm1,xmm0,xmm16              ;var_means[i] = sum / n_obvs
        vmovsd real8 ptr [rdx+rax*8],xmm1   ;save var_means[i]
        jmp Loop1

;----------------------------------------------------------------------
; Calculate covariance matrix
;
; General-purpose register use in code that calculates cov_mat[i][j]
;
;   rax     i                       r10     n_obvs 
;   rbx     j                       r11     scratch register
;   rcx     cov_mat                 r12     i * n_vars
;   rdx     var_means               r13     k
;   r8      x                       r14     i * n_obvs
;   r9      n_vars                  r15     j * n_obvs
;----------------------------------------------------------------------

CalcCV: mov rax,-1                          ;rax = i

        align 16
Loop3:  inc rax                             ;i += 1
        cmp rax,r9
        jae Done                            ;jump if i >= n_vars

        vbroadcastsd zmm18,real8 ptr [rdx+rax*8]    ;zmm18 = var_means[i]

        mov r12,rax                         ;r12 = i
        imul r12,r9                         ;r12 = i * n_vars
        mov r14,rax                         ;r14 = i
        imul r14,r10                        ;r14 = i * n_obvs
        mov rbx,-1                          ;rbx = j

        align 16
Loop4:  inc rbx                             ;j += 1
        cmp rbx,r9
        jae Loop3                           ;jump if j >= n_vars

        cmp rax,rbx                         ;is i > j?
        ja NoCalc                           ;jump if i > j (no calculation required)

        vxorpd zmm0,zmm0,zmm0                       ;sums = 0;
        vbroadcastsd zmm19,real8 ptr [rdx+rbx*8]    ;zmm19 = var_means[j]
        mov r15,rbx                                 ;r15 = j
        imul r15,r10                                ;r15 = j * n_obvs
        mov r13,-NSE                                ;r13 = k

; Calculate cov_mat[i][j] product sums
        align 16
Loop5:  add r13,NSE                         ;k += NSE
        mov r11,r10                         ;r11 = n_obvs
        sub r11,r13                         ;r11 = n_obvs - k
        cmp r11,NSE
        jb @F                               ;jump if n_objs - k < NSE

        lea r11,[r14+r13]                   ;r11 = i * n_obvs + k
        vmovupd zmm1,zmmword ptr [r8+r11*8] ;load x[i][k:k+NSE-1]
        lea r11,[r15+r13]                   ;r11 = j * n_obvs + k
        vmovupd zmm2,zmmword ptr [r8+r11*8] ;load x[j][k:k+NSE-1]
        vsubpd zmm3,zmm1,zmm18              ;x[i][k:k+NSE-1] - var_means[i]
        vsubpd zmm4,zmm2,zmm19              ;x[j][k:k+NSE-1] - var_means[j]
        vfmadd231pd zmm0,zmm3,zmm4          ;update cov_mat[i][j] product sums
        jmp Loop5

; Update cov_mat[i][j] product sums if 4 or more elements remain
@@:     vextractf64x4 ymm1,zmm0,1           ;reduce product sums (4 elements)
        vaddpd ymm0,ymm0,ymm1
        mov r11,r10                         ;r11 = n_obvs
        sub r11,r13                         ;r11 = n_obvs - k
        cmp r11,NSE/2
        jb @F                               ;jump if n_objs - k < NSE / 2

        lea r11,[r14+r13]                   ;r11 = i * n_obvs + k
        vmovupd ymm1,ymmword ptr [r8+r11*8] ;load x[i][k:k+NSE/2-1]
        lea r11,[r15+r13]                   ;r11 = j * n_obvs + k
        vmovupd ymm2,ymmword ptr [r8+r11*8] ;load x[j][k:k+NSE/2-1]
        vsubpd ymm3,ymm1,ymm18              ;x[i][k:k+NSE/2-1] - var_means[i]
        vsubpd ymm4,ymm2,ymm19              ;x[j][k:k+NSE/2-1] - var_means[j]
        vfmadd231pd ymm0,ymm3,ymm4          ;update cov_mat[i][j] product sums
        add r13,NSE/2                       ;k += NSE / 2

; Update cov_mat[i][j] product sums if 2 or more elements remain
@@:     vextractf64x2 xmm1,ymm0,1           ;reduce product sums (2 elements)
        vaddpd xmm0,xmm0,xmm1
        mov r11,r10                         ;r11 = n_obvs
        sub r11,r13                         ;r11 = n_obvs - k
        cmp r11,NSE/4
        jb @F                               ;jump if n_objs - k < NSE / 4

        lea r11,[r14+r13]                   ;r11 = i * n_obvs + k
        vmovupd xmm1,xmmword ptr [r8+r11*8] ;load x[i][k:k+NSE/4-1]
        lea r11,[r15+r13]                   ;r11 = j * n_obvs + k
        vmovupd xmm2,xmmword ptr [r8+r11*8] ;load x[j][k:k+NSE/4-1]
        vsubpd xmm3,xmm1,xmm18              ;x[i][k:k+NSE/4-1] - var_means[i]
        vsubpd xmm4,xmm2,xmm19              ;x[j][k:k+NSE/4-1] - var_means[j]
        vfmadd231pd xmm0,xmm3,xmm4          ;update cov_mat[i][j] product sums
        add r13,NSE/4                       ;k += NSE / 4

; Update cov_mat[i][j] product sums if 1 element remains
@@:     vhaddpd xmm0,xmm0,xmm0              ;reduce product sums (scalar element)
        cmp r13,r10
        jae @F                              ;jump if k >= n_obvs

        lea r11,[r14+r13]                   ;r11 = i * n_obvs + k
        vmovsd xmm1,real8 ptr [r8+r11*8]    ;load x[i][k]
        lea r11,[r15+r13]                   ;r11 = j * n_obvs + k
        vmovsd xmm2,real8 ptr [r8+r11*8]    ;load x[j][k]
        vsubsd xmm3,xmm1,xmm18              ;x[i][j] - var_means[i]
        vsubsd xmm4,xmm2,xmm19              ;x[j][i] - var_means[j]
        vfmadd231sd xmm0,xmm3,xmm4          ;update cov_mat[i][j] product sums

; Finish calculation of cov_mat[i][j]
@@:     vdivsd xmm1,xmm0,xmm17              ;calc cov_mat[i][j]
        lea r11,[r12+rbx]                   ;r11 = i * n_vars + j
        vmovsd real8 ptr [rcx+r11*8],xmm1   ;save cov_mat[i][j]
        jmp Loop4

; No calculation needed - set cov_mat[i][j] = cov_mat[j][i]
NoCalc: mov r11,rbx                         ;r11 = j
        imul r11,r9                         ;r11 = j * n_vars
        add r11,rax                         ;r11 = j * n_vars + i
        vmovsd xmm0,real8 ptr [rcx+r11*8]   ;load cov_mat[j][i]
        lea r11,[r12+rbx]                   ;r11 = i * n_vars + j
        vmovsd real8 ptr [rcx+r11*8],xmm0   ;save cov_mat[i][j]
        jmp Loop4

Done:   vzeroupper
        DeleteFrame_M rbx,r12,r13,r14,r15
        ret
CalcCovMatF64_Aavx512 endp
        end
