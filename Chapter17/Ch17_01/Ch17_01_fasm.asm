;-------------------------------------------------
;               Ch17_01_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern void MathI16_Aavx512(ZmmVal c[6], const ZmmVal* a, const ZmmVal* b);
;------------------------------------------------------------------------------

        .code
MathI16_Aavx512 proc
        vmovdqa64 zmm0,zmmword ptr [rdx]        ;load a values
        vmovdqa64 zmm1,zmmword ptr [r8]         ;load b values

        vpaddw zmm2,zmm0,zmm1                   ;packed addition - wraparound
        vmovdqa64 zmmword ptr [rcx],zmm2        ;save result

        vpaddsw zmm2,zmm0,zmm1                  ;packed addition - saturated
        vmovdqa64 zmmword ptr [rcx+64],zmm2     ;save result

        vpsubw zmm2,zmm0,zmm1                   ;packed subtraction - wraparound
        vmovdqa64 zmmword ptr [rcx+128],zmm2    ;save result

        vpsubsw zmm2,zmm0,zmm1                  ;packed subtraction - saturated
        vmovdqa64 zmmword ptr [rcx++192],zmm2   ;save result

        vpminsw zmm2,zmm0,zmm1                  ;packed min values
        vmovdqa64 zmmword ptr [rcx+256],zmm2    ;save result

        vpmaxsw zmm2,zmm0,zmm1                  ;packed max values
        vmovdqa64 zmmword ptr [rcx+320],zmm2    ;save result

        vzeroupper                              ;clear upper YMM/ZMM bits
        ret
MathI16_Aavx512 endp

;------------------------------------------------------------------------------
; extern void MathI64_Aavx512(ZmmVal c[6], const ZmmVal* a, const ZmmVal* b);
;------------------------------------------------------------------------------

MathI64_Aavx512 proc
        vmovdqa64 zmm16,zmmword ptr [rdx]       ;load a values
        vmovdqa64 zmm17,zmmword ptr [r8]        ;load b values

        vpaddq zmm18,zmm16,zmm17                ;packed qword addition
        vmovdqa64 zmmword ptr [rcx],zmm18       ;save result

        vpsubq zmm18,zmm16,zmm17                ;packed qword subtraction
        vmovdqa64 zmmword ptr [rcx+64],zmm18    ;save result

        vpmullq zmm18,zmm16,zmm17               ;packed qword multiplication
        vmovdqa64 zmmword ptr [rcx+128],zmm18   ;save products (low 64-bits)

        vpsllvq zmm18,zmm16,zmm17               ;packed qword shift left
        vmovdqa64 zmmword ptr [rcx+192],zmm18   ;save result

        vpsravq zmm18,zmm16,zmm17               ;packed qword shift right
        vmovdqa64 zmmword ptr [rcx+256],zmm18   ;save result

        vpabsq zmm18,zmm16                      ;packed qword abs (a values)
        vmovdqa64 zmmword ptr [rcx+320],zmm18   ;save result

        ret                                     ;vzeroupper not needed
MathI64_Aavx512 endp
        end
