;-------------------------------------------------
;               Ch12_01_fasm.asm
;-------------------------------------------------

               .const
r4_ScaleFtoC   real4 0.55555556                ; 5 / 9
r4_ScaleCtoF   real4 1.8                       ; 9 / 5
r4_32p0        real4 32.0

;------------------------------------------------------------------------------
; extern "C" float ConvertFtoC_Aavx(float deg_f);
;------------------------------------------------------------------------------

        .code
ConvertFtoC_Aavx proc
        vmovss xmm1,[r4_32p0]               ;xmm1 = 32
        vsubss xmm2,xmm0,xmm1               ;xmm2 = f - 32

        vmovss xmm1,[r4_ScaleFtoC]          ;xmm1 = 5 / 9
        vmulss xmm0,xmm2,xmm1               ;xmm0 = (f - 32) * 5 / 9

        ret
ConvertFtoC_Aavx endp

;------------------------------------------------------------------------------
; extern "C" float ConvertCtoF_Aavx(float deg_c);
;------------------------------------------------------------------------------

ConvertCtoF_Aavx proc
        vmulss xmm0,xmm0,[r4_ScaleCtoF]     ;xmm0 = c * 9 / 5
        vaddss xmm0,xmm0,[r4_32p0]          ;xmm0 = c * 9 / 5 + 32

        ret
ConvertCtoF_Aavx endp
        end
