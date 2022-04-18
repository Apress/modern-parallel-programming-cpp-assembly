;-------------------------------------------------
;               Ch18_02_fasm.asm
;-------------------------------------------------

        include <cmpequ.asmh>

;------------------------------------------------------------------------------
; extern "C" void PackedCompareF32_Aavx512(uint16_t c[8], const ZmmVal* a,
;   const ZmmVal* b);
;------------------------------------------------------------------------------

        .code
PackedCompareF32_Aavx512 proc
        vmovaps zmm0,zmmword ptr [rdx]      ;zmm0 = a
        vmovaps zmm1,zmmword ptr [r8]       ;zmm1 = b

        vcmpps k1,zmm0,zmm1,CMP_EQ_OQ       ;packed compare for EQ
        kmovw word ptr[rcx],k1              ;save mask

        vcmpps k1,zmm0,zmm1,CMP_NEQ_OQ      ;packed compare for NEQ
        kmovw word ptr[rcx+2],k1            ;save mask

        vcmpps k1,zmm0,zmm1,CMP_LT_OQ       ;packed compare for LT
        kmovw word ptr[rcx+4],k1            ;save mask

        vcmpps k1,zmm0,zmm1,CMP_LE_OQ       ;packed compare for LE
        kmovw word ptr[rcx+6],k1            ;save mask

        vcmpps k1,zmm0,zmm1,CMP_GT_OQ       ;packed compare for GT
        kmovw word ptr[rcx+8],k1            ;save mask

        vcmpps k1,zmm0,zmm1,CMP_GE_OQ       ;packed compare for GE
        kmovw word ptr[rcx+10],k1           ;save mask

        vcmpps k1,zmm0,zmm1,CMP_ORD_Q       ;packed compare for ORD
        kmovw word ptr[rcx+12],k1           ;save mask

        vcmpps k1,zmm0,zmm1,CMP_UNORD_Q     ;packed compare for UNORD
        kmovw word ptr[rcx+14],k1           ;save mask

        vzeroupper
        ret
PackedCompareF32_Aavx512 endp

;------------------------------------------------------------------------------
; extern "C" void PackedCompareF64_Aavx512(uint8_t c[8], const ZmmVal* a,
;   const ZmmVal* b);
;------------------------------------------------------------------------------

PackedCompareF64_Aavx512 proc
        vmovapd zmm0,zmmword ptr [rdx]      ;zmm0 = a
        vmovapd zmm1,zmmword ptr [r8]       ;zmm1 = b

        vcmppd k1,zmm0,zmm1,CMP_EQ_OQ       ;packed compare for EQ
        kmovb byte ptr[rcx],k1              ;save mask

        vcmppd k1,zmm0,zmm1,CMP_NEQ_OQ      ;packed compare for NEQ
        kmovb byte ptr[rcx+1],k1            ;save mask

        vcmppd k1,zmm0,zmm1,CMP_LT_OQ       ;packed compare for LT
        kmovb byte ptr[rcx+2],k1            ;save mask

        vcmppd k1,zmm0,zmm1,CMP_LE_OQ       ;packed compare for LE
        kmovb byte ptr[rcx+3],k1            ;save mask

        vcmppd k1,zmm0,zmm1,CMP_GT_OQ       ;packed compare for GT
        kmovb byte ptr[rcx+4],k1            ;save mask

        vcmppd k1,zmm0,zmm1,CMP_GE_OQ       ;packed compare for GE
        kmovb byte ptr[rcx+5],k1            ;save mask

        vcmppd k1,zmm0,zmm1,CMP_ORD_Q       ;packed compare for ORD
        kmovb byte ptr[rcx+6],k1            ;save mask

        vcmppd k1,zmm0,zmm1,CMP_UNORD_Q     ;packed compare for UNORD
        kmovb byte ptr[rcx+7],k1            ;save mask

        vzeroupper
        ret
PackedCompareF64_Aavx512 endp
        end
