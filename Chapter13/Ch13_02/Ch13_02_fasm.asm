;-------------------------------------------------
;               Ch13_02_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" void MulI16_Aavx(XmmVal c[2], const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

        .code
MulI16_Aavx proc
        vmovdqa xmm0,xmmword ptr [rdx]      ;xmm0 = a
        vmovdqa xmm1,xmmword ptr [r8]       ;xmm1 = b

        vpmullw xmm2,xmm0,xmm1              ;packed mul - low result
        vpmulhw xmm3,xmm0,xmm1              ;packed mul - high result

        vpunpcklwd xmm4,xmm2,xmm3           ;packed low-order dwords
        vpunpckhwd xmm5,xmm2,xmm3           ;packed high-order dwords

        vmovdqa xmmword ptr [rcx],xmm4      ;save c[0]
        vmovdqa xmmword ptr [rcx+16],xmm5   ;save c[1]
        ret
MulI16_Aavx endp

;------------------------------------------------------------------------------
; extern "C" void MulI32a_Aavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

MulI32a_Aavx proc
        vmovdqa xmm0,xmmword ptr [rdx]      ;xmm0 = a
        vmovdqa xmm1,xmmword ptr [r8]       ;xmm1 = b

        vpmulld xmm2,xmm0,xmm1              ;packed mul - low result

        vmovdqa xmmword ptr [rcx],xmm2      ;save c
        ret
MulI32a_Aavx endp

;------------------------------------------------------------------------------
; extern "C" void MulI32b_Aavx(XmmVal c[2], const XmmVal* a, const XmmVal* b);
;------------------------------------------------------------------------------

MulI32b_Aavx proc
        vmovdqa xmm0,xmmword ptr [rdx]      ;xmm0 = a
        vmovdqa xmm1,xmmword ptr [r8]       ;xmm1 = b

        vpmuldq xmm2,xmm0,xmm1              ;packed mul - a & b even dwords
        vpsrldq xmm3,xmm0,4                 ;shift a_vals right 4 bytes
        vpsrldq xmm4,xmm1,4                 ;shift b_vals right 4 bytes
        vpmuldq xmm5,xmm3,xmm4              ;packed mul - a & b odd dwords

        vpextrq qword ptr [rcx],xmm2,0      ;save qword product 0
        vpextrq qword ptr [rcx+8],xmm5,0    ;save qword product 1
        vpextrq qword ptr [rcx+16],xmm2,1   ;save qword product 2
        vpextrq qword ptr [rcx+24],xmm5,1   ;save qword product 3
        ret
MulI32b_Aavx endp
        end
