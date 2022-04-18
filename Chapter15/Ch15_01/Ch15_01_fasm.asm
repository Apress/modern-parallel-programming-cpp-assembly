;-------------------------------------------------
;               Ch15_01_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" void MathI16_Aavx2(YmmVal c[6], const YmmVal* a, const YmmVal* b);
;------------------------------------------------------------------------------

        .code
MathI16_Aavx2 proc
        vmovdqa ymm0,ymmword ptr [rdx]      ;ymm0 = a
        vmovdqa ymm1,ymmword ptr [r8]       ;ymm1 = b

        vpaddw ymm2,ymm0,ymm1               ;packed addition - wraparound
        vmovdqa ymmword ptr [rcx],ymm2

        vpaddsw ymm2,ymm0,ymm1              ;packed addition - saturated
        vmovdqa ymmword ptr [rcx+32],ymm2

        vpsubw ymm2,ymm0,ymm1               ;packed subtraction - wraparound
        vmovdqa ymmword ptr [rcx+64],ymm2

        vpsubsw ymm2,ymm0,ymm1              ;packed subtraction - saturated
        vmovdqa ymmword ptr [rcx+96],ymm2

        vpminsw ymm2,ymm0,ymm1              ;packed minimum
        vmovdqa ymmword ptr [rcx+128],ymm2

        vpmaxsw ymm2,ymm0,ymm1              ;packed maximum
        vmovdqa ymmword ptr [rcx+160],ymm2

        vzeroupper
        ret
MathI16_Aavx2 endp

;------------------------------------------------------------------------------
; extern "C" void MathI32_Aavx2(YmmVal c[6], const YmmVal* a, const YmmVal* b);
;------------------------------------------------------------------------------

MathI32_Aavx2 proc
        vmovdqa ymm0,ymmword ptr [rdx]      ;ymm0 = a
        vmovdqa ymm1,ymmword ptr [r8]       ;ymm1 = b

        vpaddd ymm2,ymm0,ymm1               ;packed addition
        vmovdqa ymmword ptr [rcx],ymm2

        vpsubd ymm2,ymm0,ymm1               ;packed subtraction
        vmovdqa ymmword ptr [rcx+32],ymm2

        vpmulld ymm2,ymm0,ymm1              ;packed multiplication (low result)
        vmovdqa ymmword ptr [rcx+64],ymm2

        vpsllvd ymm2,ymm0,ymm1              ;packed shift left logical
        vmovdqa ymmword ptr [rcx+96],ymm2

        vpsravd ymm2,ymm0,ymm1              ;packed shift right arithmetic
        vmovdqa ymmword ptr [rcx+128],ymm2

        vpabsd ymm2,ymm0                    ;packed absolute value
        vmovdqa ymmword ptr [rcx+160],ymm2

        vzeroupper
        ret
MathI32_Aavx2 endp
        end
