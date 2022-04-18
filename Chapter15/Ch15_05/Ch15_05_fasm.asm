;-------------------------------------------------
;               Ch15_05_fasm.asm
;-------------------------------------------------

            .const
r4_1p0      real4 1.0
r4_255p0    real4 255.0

;------------------------------------------------------------------------------
; extern "C" void ConvertU8ToF32_Aavx2(float* pb_des, const uint8_t* pb_src,
;   size_t num_pixels);
;------------------------------------------------------------------------------

        extern g_NumPixelsMax:qword
        extern g_LUT_U8ToF32:qword
NSE     equ 32                              ;num_simd_elements

        .code
ConvertU8ToF32_Aavx2 proc

; Validate arguments
        test r8,r8
        jz Done                             ;jump if num_pixels == 0
        cmp r8,[g_NumPixelsMax]
        ja Done                             ;jump if num_pixels > g_NumPixelsMax

        test rcx,1fh
        jnz Done                            ;jump if pb_des not 32b aligned
        test rdx,1fh
        jnz Done                            ;jump if pb_src not 32b aligned

; Initialize
        mov rax,-NSE                        ;initialize i
        lea r9,[g_LUT_U8ToF32]              ;r9 = pointer to LUT
        vpcmpeqb ymm5,ymm5,ymm5             ;ymm5 = all ones

; Main processing loop
Loop1:  add rax,NSE                         ;i += NSE
        mov r10,r8                          ;r10 = num_pixels
        sub r10,rax                         ;r10 = num_pixels - i
        cmp r10,NSE                         ;num_pixels - i < NSE?
        jb @F                               ;jump if yes

; Convert pixels from U8 to F32 using LUT
        vpmovzxbd ymm0,qword ptr [rdx+rax]      ;ymm0 = pb_src[i:i+7] (U32)
        vmovdqa ymm1,ymm5                       ;ymm1 = vgatherdps load mask
        vgatherdps ymm2,[r9+ymm0*4],ymm1        ;ymm2 = pb_src[i:i+7] (F32)
        vmovaps ymmword ptr [rcx+rax*4],ymm2    ;save pb_des[i:i+7]

        vpmovzxbd ymm0,qword ptr [rdx+rax+8]    ;ymm0 = pb_src[i+8:i+15] (U32)
        vmovdqa ymm1,ymm5                       ;ymm1 = vgatherdps load mask
        vgatherdps ymm2,[r9+ymm0*4],ymm1        ;ymm2 = pb_src[i_8:i+15] (F32)
        vmovaps ymmword ptr [rcx+rax*4+32],ymm2 ;save pb_des[i+8:i+15]

        vpmovzxbd ymm0,qword ptr [rdx+rax+16]   ;ymm0 = pb_src[i+16:i+23] (U32)
        vmovdqa ymm1,ymm5                       ;ymm1 = vgatherdps load mask
        vgatherdps ymm2,[r9+ymm0*4],ymm1        ;ymm2 = pb_src[i+16:i+23] (F32)
        vmovaps ymmword ptr [rcx+rax*4+64],ymm2 ;save pb_des[i+16:i+23]

        vpmovzxbd ymm0,qword ptr [rdx+rax+24]   ;ymm0 = pb_src[i+24:i+31] (U32)
        vmovdqa ymm1,ymm5                       ;ymm1 = vgatherdps load mask
        vgatherdps ymm2,[r9+ymm0*4],ymm1        ;ymm2 = pb_src[i+24:i+31] (F32)
        vmovaps ymmword ptr [rcx+rax*4+96],ymm2 ;save pb_des[i+24:i+31]

        jmp Loop1

; Process any residual pixels
@@:     cmp rax,r8
        jae Done                            ;jump if i >= num_pixels

Loop2:  movzx r10d,byte ptr [rdx+rax]       ;load pb_src[i]
        vmovss xmm0,real4 ptr [r9+r10*4]    ;convert to F32 using LUT
        vmovss real4 ptr [rcx+rax*4],xmm0   ;save pb_des[i]

        inc rax                             ;i += 1
        cmp rax,r8
        jb Loop2                            ;jump if i < num_pixels

Done:   vzeroupper
        ret
ConvertU8ToF32_Aavx2 endp
        end
