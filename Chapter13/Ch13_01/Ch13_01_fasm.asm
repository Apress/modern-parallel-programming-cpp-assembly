;-------------------------------------------------
;               Ch13_01_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" void AddI16_Aavx(XmmVal* c1, XmmVal* c2, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

        .code
AddI16_Aavx proc
        vmovdqa xmm0,xmmword ptr [r8]       ;xmm0 = a
        vmovdqa xmm1,xmmword ptr [r9]       ;xmm1 = b

        vpaddw xmm2,xmm0,xmm1               ;packed add - wraparound
        vpaddsw xmm3,xmm0,xmm1              ;packed add - saturated

        vmovdqa xmmword ptr [rcx],xmm2      ;save c1
        vmovdqa xmmword ptr [rdx],xmm3      ;save c2
        ret
AddI16_Aavx endp

;------------------------------------------------------------------------------
; extern "C" void SubI16_Aavx(XmmVal* c1, XmmVal* c2, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

SubI16_Aavx proc
        vmovdqa xmm0,xmmword ptr [r8]       ;xmm0 = a
        vmovdqa xmm1,xmmword ptr [r9]       ;xmm1 = b

        vpsubw xmm2,xmm0,xmm1               ;packed sub - wraparound
        vpsubsw xmm3,xmm0,xmm1              ;packed sub - saturated

        vmovdqa xmmword ptr [rcx],xmm2      ;save c1
        vmovdqa xmmword ptr [rdx],xmm3      ;save c2
        ret
SubI16_Aavx endp
        end
