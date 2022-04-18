;-------------------------------------------------
;               Ch13_03_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" void AndU16_Aavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

        .code
AndU16_Aavx proc
        vmovdqa xmm0,xmmword ptr [rdx]      ;xmm0 = a
        vmovdqa xmm1,xmmword ptr [r8]       ;xmm1 = b

        vpand xmm2,xmm0,xmm1                ;bitwise and

        vmovdqa xmmword ptr [rcx],xmm2      ;save result
        ret
AndU16_Aavx endp

;------------------------------------------------------------------------------
; extern "C" void OrU16_Aavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

OrU16_Aavx proc
        vmovdqa xmm0,xmmword ptr [rdx]      ;xmm0 = a
        vmovdqa xmm1,xmmword ptr [r8]       ;xmm1 = b

        vpor xmm2,xmm0,xmm1                 ;bitwise or

        vmovdqa xmmword ptr [rcx],xmm2      ;save result
        ret
OrU16_Aavx endp

;------------------------------------------------------------------------------
; extern "C" void XorU16_Aavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

XorU16_Aavx proc
        vmovdqa xmm0,xmmword ptr [rdx]      ;xmm0 = a
        vmovdqa xmm1,xmmword ptr [r8]       ;xmm1 = b

        vpxor xmm2,xmm0,xmm1                ;bitwise xor

        vmovdqa xmmword ptr [rcx],xmm2      ;save result
        ret
XorU16_Aavx endp
        end
