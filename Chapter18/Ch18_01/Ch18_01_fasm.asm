;-------------------------------------------------
;               Ch18_01_fasm.asm
;-------------------------------------------------

            .const
r8_AbsMask  qword 07fffffffffffffffh
r4_AbsMask  dword 07fffffffh

;------------------------------------------------------------------------------
; extern "C" void PackedMathF32_Aavx512(ZmmVal c[9], const ZmmVal* a,
;   const ZmmVal* b);
;------------------------------------------------------------------------------

        .code
PackedMathF32_Aavx512 proc
        vmovaps zmm0,zmmword ptr [rdx]      ;zmm0 = a
        vmovaps zmm1,zmmword ptr [r8]       ;zmm1 = b

        vaddps zmm2,zmm0,zmm1               ;SPFP addition
        vmovaps zmmword ptr[rcx],zmm2

        vaddps zmm2,zmm0,zmm1{rd-sae}       ;SPFP addition (round down toward -inf)
        vmovaps zmmword ptr[rcx+64],zmm2

        vsubps zmm2,zmm0,zmm1               ;SPFP subtraction
        vmovaps zmmword ptr[rcx+128],zmm2

        vmulps zmm2,zmm0,zmm1               ;SPFP multiplication
        vmovaps zmmword ptr[rcx+192],zmm2

        vdivps zmm2,zmm0,zmm1               ;SPFP division
        vmovaps zmmword ptr[rcx+256],zmm2

        vminps zmm2,zmm0,zmm1               ;SPFP min
        vmovaps zmmword ptr[rcx+320],zmm2
        
        vmaxps zmm2,zmm0,zmm1               ;SPFP max
        vmovaps zmmword ptr[rcx+384],zmm2

        vsqrtps zmm2,zmm0                   ;SPFP sqrt(a)
        vmovaps zmmword ptr[rcx+448],zmm2

        vandps zmm2,zmm1,real4 bcst [r4_AbsMask]    ;SPFP abs(b)
        vmovaps zmmword ptr[rcx+512],zmm2

        vzeroupper
        ret
PackedMathF32_Aavx512 endp

;------------------------------------------------------------------------------
; extern "C" void PackedMathF64_Aavx512(ZmmVal c[9], const ZmmVal* a,
;   const ZmmVal* b);
;------------------------------------------------------------------------------

PackedMathF64_Aavx512 proc
        vmovapd zmm0,zmmword ptr [rdx]      ;zmm0 = a
        vmovapd zmm1,zmmword ptr [r8]       ;zmm1 = b

        vaddpd zmm2,zmm0,zmm1               ;DPFP addition
        vmovapd zmmword ptr[rcx],zmm2

        vsubpd zmm2,zmm0,zmm1               ;DPFP subtraction
        vmovapd zmmword ptr[rcx+64],zmm2

        vmulpd zmm2,zmm0,zmm1               ;DPFP multiplication
        vmovapd zmmword ptr[rcx+128],zmm2

        vdivpd zmm2,zmm0,zmm1               ;DPFP division
        vmovapd zmmword ptr[rcx+192],zmm2

        vdivpd zmm2,zmm0,zmm1{ru-sae}       ;DPFP division (round up toward +inf)
        vmovapd zmmword ptr[rcx+256],zmm2

        vminpd zmm2,zmm0,zmm1               ;DPFP min
        vmovapd zmmword ptr[rcx+320],zmm2
        
        vmaxpd zmm2,zmm0,zmm1               ;DPFP max
        vmovapd zmmword ptr[rcx+384],zmm2

        vsqrtpd zmm2,zmm0                   ;DPFP sqrt(a)
        vmovapd zmmword ptr[rcx+448],zmm2

        vandpd zmm2,zmm1,real8 bcst [r8_AbsMask]    ;DPFP abs(b)
        vmovapd zmmword ptr[rcx+512],zmm2

        vzeroupper
        ret
PackedMathF64_Aavx512 endp
        end
