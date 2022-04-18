;-------------------------------------------------
;               Ch16_04_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; Mat4x4TransposeF32_M macro
;
; Description:  This macro transposes a 4x4 matrix of single-precision
;               floating-point values.
;
;  Input Matrix                    Output Matrix
;  ---------------------------------------------------
;  xmm0    a3 a2 a1 a0             xmm0    d0 c0 b0 a0
;  xmm1    b3 b2 b1 b0             xmm1    d1 c1 b1 a1
;  xmm2    c3 c2 c1 c0             xmm2    d2 c2 b2 a2
;  xmm3    d3 d2 d1 d0             xmm3    d3 c3 b3 a3
;
; Scratch registers: xmm4, xmm5
;------------------------------------------------------------------------------

Mat4x4TransposeF32_M macro
        vunpcklps xmm4,xmm0,xmm1            ;xmm4 = b1 a1 b0 a0
        vunpckhps xmm0,xmm0,xmm1            ;xmm0 = b3 a3 b2 a2
        vunpcklps xmm5,xmm2,xmm3            ;xmm5 = d1 c1 d0 c0
        vunpckhps xmm1,xmm2,xmm3            ;xmm1 = d3 c3 d2 c2

        vmovlhps xmm2,xmm0,xmm1             ;xmm2 = d2 c2 b2 a2
        vmovhlps xmm3,xmm1,xmm0             ;xmm3 = d3 c3 b3 a3
        vmovlhps xmm0,xmm4,xmm5             ;xmm0 = d0 c0 b0 a0
        vmovhlps xmm1,xmm5,xmm4             ;xmm1 = d1 c1 b1 a1
        endm

;------------------------------------------------------------------------------
; extern "C" void MatVecMulF32_Aavx2(Vec4x1_F32* vec_b, const float* m,
;   const Vec4x1_F32* vec_a, size_t num_vec);
;------------------------------------------------------------------------------

        .code
MatVecMulF32_Aavx2 proc

; Validate arguments
        test r9,r9
        jz Done                             ;jump if num_vec == 0
        test rcx,1fh
        jnz Done                            ;jump if vec_b not 32b aligned
        test rdx,1fh
        jnz Done                            ;jump if m not 32b aligned
        test r8,1fh
        jnz Done                            ;jump if vec_a 32b aligned

; Initialize
        mov rax,-16                         ;array offset
        vmovaps ymm0,ymmword ptr [rdx]      ;xmm0 = m row 0
        vextractf128 xmm1,ymm0,1            ;xmm1 = m ro1 1
        vmovaps ymm2,ymmword ptr [rdx+32]   ;xmm2 = m row 2
        vextractf128 xmm3,ymm2,1            ;xmm3 = m row 3

; Transpose m
        Mat4x4TransposeF32_M

; Calculate matrix-vector products
        align 16
Loop1:  add rax,16

        vbroadcastss xmm5,real4 ptr [r8+rax]    ;xmm5 = vec_a[i].W
        vmulps xmm4,xmm0,xmm5                   ;xmm4  = m_T row 0 * W vals

        vbroadcastss xmm5,real4 ptr [r8+rax+4]  ;xmm5 = vec_a[i].X
        vfmadd231ps xmm4,xmm1,xmm5              ;xmm4 += m_T row 1 * X vals

        vbroadcastss xmm5,real4 ptr [r8+rax+8]  ;xmm5 = vec_a[i].Y
        vfmadd231ps xmm4,xmm2,xmm5              ;xmm4 += m_T row 2 * Y vals

        vbroadcastss xmm5,real4 ptr [r8+rax+12] ;xmm5 = vec_a[i].Z
        vfmadd231ps xmm4,xmm3,xmm5              ;xmm4 += m_T row 3 * Z vals

        vmovaps xmmword ptr [rcx+rax],xmm4      ;save vec_b[i]

        dec r9                                  ;num_vec -= 1
        jnz Loop1                               ;repeat until done

Done:   vzeroupper
        ret
MatVecMulF32_Aavx2 endp
        end
