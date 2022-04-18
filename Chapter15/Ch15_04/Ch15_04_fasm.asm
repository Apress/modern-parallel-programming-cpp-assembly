;-------------------------------------------------
;               Ch15_04_fasm.asm
;-------------------------------------------------

            include <MacrosX86-64-AVX.asmh>

;------------------------------------------------------------------------------
; extern "C" void ConvertRgbToGs_Aavx2(uint8_t* pb_gs, const RGB32* pb_rgb,
;   size_t num_pixels, const float coef[4]);
;------------------------------------------------------------------------------

            .const
r4_0p5      real4 0.5
r4_255p0    real4 255.0
i4_0xff     dword 0ffh

NSE         equ 8                           ;num_simd_elements

        extern g_NumPixelsMax:qword

        .code
ConvertRgbToGs_Aavx2 proc frame
        CreateFrame_M CD_,0,64
        SaveXmmRegs_M xmm12,xmm13,xmm14,xmm15
        EndProlog_M

; Validate argument values
        test rcx,1fh
        jnz Done                            ;jump if pb_gs not 32b aligned
        test rdx,1fh
        jnz Done                            ;jump if pb_rgb not 32b aligned

        cmp r8,[g_NumPixelsMax]
        ja Done                             ;jump if num_pixels > g_NumPixelsMax
        test r8,07h
        jnz Done                            ;jump if num_pixels not multiple of 8

        vxorps xmm0,xmm0,xmm0               ;xmm0 = 0.0

        vmovss xmm13,real4 ptr [r9]         ;xmm13 = coef[0]
        vcomiss xmm13,xmm0
        jb Done                             ;jump if coef[0] < 0.0
        
        vmovss xmm14,real4 ptr [r9+4]       ;xmm14 = coef[1]
        vcomiss xmm14,xmm0
        jb Done                             ;jump if coef[1] < 0.0

        vmovss xmm15,real4 ptr [r9+8]       ;xmm15 = coef[2]
        vcomiss xmm15,xmm0
        jb  Done                            ;jump if coef[2] < 0.0

; Initialize
        vbroadcastss ymm4,real4 ptr [r4_0p5]    ;packed 0.5
        vbroadcastss ymm5,real4 ptr [r4_255p0]  ;packed 255.0

        vpbroadcastd ymm12,[i4_0xff]            ;packed 0x000000ff

        vbroadcastss ymm13,xmm13                ;packed coef[0]
        vbroadcastss ymm14,xmm14                ;packed coef[1]
        vbroadcastss ymm15,xmm15                ;packed coef[2]

        mov rax,-NSE                            ;initialize i

; Convert pixels from RGB to gray scale
Loop1:  add rax,NSE                         ;i += NSE
        cmp rax,r8
        jae Done                            ;jump if i >= num_pixels

        vmovdqa ymm0,ymmword ptr [rdx+rax*4]  ;load next block of 8 RGB32 pixels

        vpand ymm1,ymm0,ymm12               ;ymm1 = r values (dwords)
        vpsrld ymm0,ymm0,8
        vpand ymm2,ymm0,ymm12               ;ymm2 = g values (dwords)
        vpsrld ymm0,ymm0,8
        vpand ymm3,ymm0,ymm12               ;ymm3 = b values (dwords)

        vcvtdq2ps ymm1,ymm1                 ;ymm1 = r values (F32)
        vcvtdq2ps ymm2,ymm2                 ;ymm2 = g values (F32)
        vcvtdq2ps ymm3,ymm3                 ;ymm3 = b values (F32)

        vmulps ymm1,ymm1,ymm13              ;ymm1 = r values * coef[0]
        vmulps ymm2,ymm2,ymm14              ;ymm2 = g values * coef[1]
        vmulps ymm3,ymm3,ymm15              ;ymm3 = b values * coef[2]

        vaddps ymm0,ymm1,ymm2               ;ymm0 = sum of r and g values
        vaddps ymm1,ymm3,ymm4               ;ymm1 = sum of b values and 0.5
        vaddps ymm0,ymm0,ymm1               ;ymm0 = sum of r, g, b, and 0.5

        vminps ymm1,ymm0,ymm5               ;clip grayscale values to 255.0

        vcvtps2dq ymm0,ymm1                 ;convert F32 values to dword
        vpackusdw ymm1,ymm0,ymm0            ;convert dwords to words
        vpermq ymm2,ymm1,10001000b          ;ymm2[127:0] = 8 grayscale words
        vpackuswb ymm3,ymm2,ymm2            ;ymm3[63:0] = 8 grayscale bytes

        vmovq qword ptr [rcx+rax],xmm3      ;save pb_gs[i:i+7]
        jmp Loop1

Done:   vzeroupper
        RestoreXmmRegs_M xmm12,xmm13,xmm14,xmm15
        DeleteFrame_M
        ret
ConvertRgbToGs_Aavx2 endp
        end
