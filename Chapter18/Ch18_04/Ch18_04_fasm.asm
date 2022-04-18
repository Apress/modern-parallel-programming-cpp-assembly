;-------------------------------------------------
;               Ch18_04_fasm.asm
;-------------------------------------------------

        include <MacrosX86-64-AVX.asmh>

;------------------------------------------------------------------------------
; extern "C" void MatrixMulF32_Aavx512_TEST(float* c, const float* a, const float* b,
;   const size_t* sizes);
;------------------------------------------------------------------------------

NSE     equ 16                                  ;num_simd_elements
NSE_MOD equ 0fh                                 ;mask to calculate num_residual_cols

        .code
MatrixMulF32_Aavx512 proc frame
        CreateFrame_M MM_,0,0,rbx,rsi,rdi,r12,r13,r14,r15
        EndProlog_M

; Load matrix sizes
        mov r13,qword ptr [r9]                  ;r13 = c_nrows
        mov r14,qword ptr [r9+8]                ;r14 = c_ncols (also b_ncols)
        mov r15,qword ptr [r9+16]               ;r15 = a_ncols

; Calculate mask for resdiual column load and store
        mov r12,r14                             ;r12 = c_ncols
        and r12,NSE_MOD                         ;num_residual_cols = c_ncols % NSE

        mov r9,rcx                              ;save rcx
        mov rcx,r12                             ;rcx = num_residual_cols
        mov eax,1
        shl eax,cl                              ;eax = 2 ** num_residual_cols
        dec eax                                 ;eax = 2 ** num_residual_cols - 1
        kmovw k1,eax                            ;k1 = mask for residual col load/store
        mov rcx,r9                              ;restore rcx

        mov rax,-1                              ;rax = i

;------------------------------------------------------------------------------
; General-purpose registers used in code below
;   rax     i                                       r9      j
;   rbx     matrix a element pointer (p_aa)         r10     k
;   rcx     matrix c                                r11     scratch
;   rdx     matrix a                                r12     num_residual_cols
;   rsi     matrix b element pointer (p_bb)         r13     c_nrows
;   rdi     &a[i][0]                                r14     c_ncols (b_ncols)
;   r8      matrix b                                r15     a_ncols
;------------------------------------------------------------------------------

; Repeat for each row in c
        align 16
Loop1:  inc rax                                 ;i += 1
        cmp rax,r13
        jae Done                                ;jump if i >= c_nrows

        mov rdi,rdx                             ;rdi = &a[i][0]
        lea rdx,[rdx+r15*4]                     ;rdx = &a[i+1][0]
        xor r9,r9                               ;j = 0

; Calculate c[i][j:j+NSE*2-1]
        align 16
Loop2:  lea r11,[r9+NSE*2]                      ;r11 = j + NSE*2
        cmp r11,r14
        ja @F                                   ;jump if j + NSE*2 > c_ncols

        mov rbx,rdi                             ;rbx = &a[i][0]
        lea rsi,[r8+r9*4]                       ;rsi = &b[0][j]
        vxorps zmm2,zmm2,zmm2                   ;c_vals[i][j:j+NSE-1] = 0
        vxorps zmm3,zmm3,zmm3                   ;c_vals[i][j+NSE:j+NSE*2-1] = 0
        mov r10,r15                             ;k = a_ncols

        align 16
Loop3:  vbroadcastss zmm0,real4 ptr [rbx]          ;broadcast a[i][k]
        vfmadd231ps zmm2,zmm0,zmmword ptr [rsi]    ;zmm2 += a[i][k] * b[k][j:j+NSE-1]
        vfmadd231ps zmm3,zmm0,zmmword ptr [rsi+64] ;zmm3 += a[i][k] * b[k][j+NSE:j+NSE*2-1]

        add rbx,4                               ;rbx = &a[i][k+1]
        lea rsi,[rsi+r14*4]                     ;rsi = &b[k+1][j]
        dec r10                                 ;k -= 1
        jnz Loop3                               ;repeat until done

        vmovups zmmword ptr[rcx],zmm2           ;save c[i][j:j+NSE-1]
        vmovups zmmword ptr[rcx+64],zmm3        ;save c[i][j+NSE:j+NSE*2-1]

        add r9,NSE*2                            ;j += NSE * 2
        add rcx,NSE*2*4                         ;rcx = &c[i][j+NSE*2]
        jmp Loop2

; Calculate c[i][j:j+NSE-1]
@@:     lea r11,[r9+NSE]                        ;r11 = j + NSE
        cmp r11,r14
        ja @F                                   ;jump if j + NSE > c_ncols

        mov rbx,rdi                             ;rbx = &a[i][0]
        lea rsi,[r8+r9*4]                       ;rsi = &b[0][j]
        vxorps zmm2,zmm2,zmm2                   ;c_vals[i][j:j+NSE-1] = 0
        mov r10,r15                             ;k = a_ncols

        align 16
Loop4:  vbroadcastss zmm0,real4 ptr [rbx]       ;broadcast a[i][k]
        vfmadd231ps zmm2,zmm0,zmmword ptr [rsi] ;zmm2 += a[i][k] * b[k][j:j+NSE-1]

        add rbx,4                               ;rbx = &a[i][k+1]
        lea rsi,[rsi+r14*4]                     ;rsi = &b[k+1][j]
        dec r10                                 ;k -= 1
        jnz Loop4                               ;repeat until done

        vmovups zmmword ptr[rcx],zmm2           ;save c[i][j:j+NSE-1]

        add r9,NSE                              ;j += NSE
        add rcx,NSE*4                           ;rcx = &c[i][j+NSE]
        jmp Loop2

; Calculate c[i][j:j+NRC] (NRC is num_residual_cols)
@@:     test r12,r12                            ;num_residual_cols == 0?
        jz Loop1                                ;jump if yes

        mov rbx,rdi                             ;rbx = &a[i][0]
        lea rsi,[r8+r9*4]                       ;rsi = &b[0][j]
        vxorps zmm2,zmm2,zmm2                   ;c_vals[i][j:j+NRC] = 0
        mov r10,r15                             ;k = a_ncols

        align 16
Loop5:  vbroadcastss zmm0,real4 ptr [rbx]       ;broadcast a[i][k]
        vmovups zmm1{k1},zmmword ptr [rsi]      ;load b[k][j:j+NRC]
        vfmadd231ps zmm2,zmm0,zmm1              ;zmm2 += a[i][k] * b[k][j:j+NRC]

        add rbx,4                               ;rbx = &a[i][k+1]
        lea rsi,[rsi+r14*4]                     ;rsi = &b[k+1][j]
        dec r10                                 ;k -= 1
        jnz Loop5                               ;repeat until done

        vmovups zmmword ptr [rcx]{k1},zmm2      ;save c[i][j:j+NRC]

        lea rcx,[rcx+r12*4]                     ;rcx = &c[i+1][0]
        jmp Loop1

Done:   vzeroupper
        DeleteFrame_M rbx,rsi,rdi,r12,r13,r14,r15
        ret
MatrixMulF32_Aavx512 endp
        end
