;-------------------------------------------------
;               Ch13_04_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern void SllU16_Aavx(XmmVal* c, const XmmVal* a, int count);
;------------------------------------------------------------------------------

        .code
SllU16_Aavx proc
        vmovdqa xmm0,xmmword ptr [rdx]      ;xmm0 = a
        vmovd xmm1,r8d                      ;xmm1[31:0] = count

        vpsllw xmm2,xmm0,xmm1               ;left shift word elements of a

        vmovdqa xmmword ptr [rcx],xmm2      ;save result
        ret
SllU16_Aavx endp

;------------------------------------------------------------------------------
; extern void SrlU16_Aavx(XmmVal* c, const XmmVal* a, int count);
;------------------------------------------------------------------------------

SrlU16_Aavx proc
        vmovdqa xmm0,xmmword ptr [rdx]      ;xmm0 = a
        vmovd xmm1,r8d                      ;xmm1[31:0] = count

        vpsrlw xmm2,xmm0,xmm1               ;right shift word elements of a

        vmovdqa xmmword ptr [rcx],xmm2      ;save result
        ret
SrlU16_Aavx endp

;------------------------------------------------------------------------------
; extern void SraU16_Aavx(XmmVal* c, const XmmVal* a, int count);
;------------------------------------------------------------------------------

SraU16_Aavx proc
        vmovdqa xmm0,xmmword ptr [rdx]      ;xmm0 = a
        vmovd xmm1,r8d                      ;xmm1[31:0] = count

        vpsraw xmm2,xmm0,xmm1               ;right shift word elements of a

        vmovdqa xmmword ptr [rcx],xmm2      ;save result
        ret
SraU16_Aavx endp
        end
