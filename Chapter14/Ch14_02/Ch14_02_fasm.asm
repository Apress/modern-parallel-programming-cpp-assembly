;-------------------------------------------------
;               Ch14_02_fasm.asm
;-------------------------------------------------

        include <cmpequ.asmh>

;------------------------------------------------------------------------------
; extern "C" void PackedCompareF32_Aavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
;------------------------------------------------------------------------------

        .code
PackedCompareF32_Aavx proc
        vmovaps ymm0,ymmword ptr [rdx]      ;ymm0 = a
        vmovaps ymm1,ymmword ptr [r8]       ;ymm1 = b

        vcmpps ymm2,ymm0,ymm1,CMP_EQ_OQ     ;packed compare for EQ
        vmovaps ymmword ptr[rcx],ymm2

        vcmpps ymm2,ymm0,ymm1,CMP_NEQ_OQ    ;packed compare for NEQ
        vmovaps ymmword ptr[rcx+32],ymm2

        vcmpps ymm2,ymm0,ymm1,CMP_LT_OQ     ;packed compare for LT
        vmovaps ymmword ptr[rcx+64],ymm2

        vcmpps ymm2,ymm0,ymm1,CMP_LE_OQ     ;packed compare for LE
        vmovaps ymmword ptr[rcx+96],ymm2

        vcmpps ymm2,ymm0,ymm1,CMP_GT_OQ     ;packed compare for GT
        vmovaps ymmword ptr[rcx+128],ymm2

        vcmpps ymm2,ymm0,ymm1,CMP_GE_OQ     ;packed compare for GE
        vmovaps ymmword ptr[rcx+160],ymm2

        vcmpps ymm2,ymm0,ymm1,CMP_ORD_Q     ;packed compare for ORD
        vmovaps ymmword ptr[rcx+192],ymm2

        vcmpps ymm2,ymm0,ymm1,CMP_UNORD_Q   ;packed compare for UNORD
        vmovaps ymmword ptr[rcx+224],ymm2

        vzeroupper
        ret
PackedCompareF32_Aavx endp

;------------------------------------------------------------------------------
; extern "C" void PackedCompareF64_Aavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
;------------------------------------------------------------------------------

PackedCompareF64_Aavx proc
        vmovapd ymm0,ymmword ptr [rdx]      ;ymm0 = a
        vmovapd ymm1,ymmword ptr [r8]       ;ymm1 = b

        vcmppd ymm2,ymm0,ymm1,CMP_EQ_OQ     ;packed compare for EQ
        vmovapd ymmword ptr[rcx],ymm2

        vcmppd ymm2,ymm0,ymm1,CMP_NEQ_OQ    ;packed compare for NEQ
        vmovapd ymmword ptr[rcx+32],ymm2

        vcmppd ymm2,ymm0,ymm1,CMP_LT_OQ     ;packed compare for LT
        vmovapd ymmword ptr[rcx+64],ymm2

        vcmppd ymm2,ymm0,ymm1,CMP_LE_OQ     ;packed compare for LE
        vmovapd ymmword ptr[rcx+96],ymm2

        vcmppd ymm2,ymm0,ymm1,CMP_GT_OQ     ;packed compare for GT
        vmovapd ymmword ptr[rcx+128],ymm2

        vcmppd ymm2,ymm0,ymm1,CMP_GE_OQ     ;packed compare for GE
        vmovapd ymmword ptr[rcx+160],ymm2

        vcmppd ymm2,ymm0,ymm1,CMP_ORD_Q     ;packed compare for ORD
        vmovapd ymmword ptr[rcx+192],ymm2

        vcmppd ymm2,ymm0,ymm1,CMP_UNORD_Q   ;packed compare for UNORD
        vmovapd ymmword ptr[rcx+224],ymm2

        vzeroupper
        ret
PackedCompareF64_Aavx endp
        end
