;-------------------------------------------------
;               Ch15_02_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" void ZeroExtU8_U16_Aavx2(YmmVal c[2], YmmVal* a);
;------------------------------------------------------------------------------
        
        .code
ZeroExtU8_U16_Aavx2 proc
        vmovdqa ymm0,ymmword ptr [rdx]      ;ymm0 = a (32 byte values)
        vextracti128 xmm1,ymm0,1            ;xmm1 = high-order byte values

        vpmovzxbw ymm2,xmm0                 ;zero extend a[0:15] to word
        vpmovzxbw ymm3,xmm1                 ;zero extend a[16:31] to words

        vmovdqa ymmword ptr [rcx],ymm2      ;save words c[0:15]
        vmovdqa ymmword ptr [rcx+32],ymm3   ;save words c[16:31]

        vzeroupper
        ret
ZeroExtU8_U16_Aavx2 endp

;------------------------------------------------------------------------------
; extern "C" void ZeroExtU8_U32_Aavx2(YmmVal c[4], YmmVal* a);
;------------------------------------------------------------------------------

ZeroExtU8_U32_Aavx2 proc
        vmovdqa ymm0,ymmword ptr [rdx]      ;ymm0 = a (32 bytes values)
        vextracti128 xmm1,ymm0,1            ;xmm1 = high-order byte values

        vpmovzxbd ymm2,xmm0                 ;zero extend a[0:7] to dword
        vpsrldq xmm0,xmm0,8                 ;xmm0[63:0] = a[8:15]
        vpmovzxbd ymm3,xmm0                 ;zero extend a[8:15] to dword

        vpmovzxbd ymm4,xmm1                 ;zero extend a[16:23] to dword
        vpsrldq xmm1,xmm1,8                 ;xmm1[63:0] = a[24:31]
        vpmovzxbd ymm5,xmm1                 ;zero extend a[24:31] to dword

        vmovdqa ymmword ptr [rcx],ymm2      ;save dwords c[0:7]
        vmovdqa ymmword ptr [rcx+32],ymm3   ;save dwords c[8:15]
        vmovdqa ymmword ptr [rcx+64],ymm4   ;save dwords c[16:23]
        vmovdqa ymmword ptr [rcx+96],ymm5   ;save dwords c[24:31]

        vzeroupper
        ret
ZeroExtU8_U32_Aavx2 endp

;------------------------------------------------------------------------------
; extern "C" void SignExtI16_I32_Aavx2(YmmVal c[2], YmmVal* a);
;------------------------------------------------------------------------------

SignExtI16_I32_Aavx2 proc
        vmovdqa ymm0,ymmword ptr [rdx]      ;ymm0 = a (16 word values)
        vextracti128 xmm1,ymm0,1            ;xmm1 = high-order word values

        vpmovsxwd ymm2,xmm0                 ;sign extend a[0:7] to dword
        vpmovsxwd ymm3,xmm1                 ;sign extend a[8:15] to dwords

        vmovdqa ymmword ptr [rcx],ymm2      ;save dwords c[0:7]
        vmovdqa ymmword ptr [rcx+32],ymm3   ;save dwords c[8:15]

        vzeroupper
        ret
SignExtI16_I32_Aavx2 endp

;------------------------------------------------------------------------------
; extern "C" void SignExtI16_I64_Aavx2(YmmVal c[4], YmmVal* a);
;------------------------------------------------------------------------------

SignExtI16_I64_Aavx2 proc
        vmovdqa ymm0,ymmword ptr [rdx]      ;ymm0 = a (16 word values)
        vextracti128 xmm1,ymm0,1            ;xmm1 = high-order word values

        vpmovsxwq ymm2,xmm0                 ;sign extend a[0:3] to qword
        vpsrldq xmm0,xmm0,8                 ;xmm0[63:0] = a[4:7]
        vpmovsxwq ymm3,xmm0                 ;sign extend a[4:7] to qword

        vpmovsxwq ymm4,xmm1                 ;sign extend a[8:11] to qword
        vpsrldq xmm1,xmm1,8                 ;xmm1[63:0] = a[12:15]
        vpmovsxwq ymm5,xmm1                 ;sign extend a[12:15] to qword

        vmovdqa ymmword ptr [rcx],ymm2      ;save qwords c[0:3]
        vmovdqa ymmword ptr [rcx+32],ymm3   ;save qwords c[4:7]
        vmovdqa ymmword ptr [rcx+64],ymm4   ;save qwords c[8:11]
        vmovdqa ymmword ptr [rcx+96],ymm5   ;save qwords c[12:16]

        vzeroupper
        ret
SignExtI16_I64_Aavx2 endp
        end
