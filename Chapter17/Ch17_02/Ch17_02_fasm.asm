;-------------------------------------------------
;               Ch17_02_fasm.asm
;-------------------------------------------------

        include <cmpequ.asmh>

;------------------------------------------------------------------------------
; void MaskOpI64a_Aavx512(ZmmVal c[5], uint8_t mask, const ZmmVal* a,
;   const ZmmVal* b);
;------------------------------------------------------------------------------

        .code
MaskOpI64a_Aavx512 proc
        vmovdqa64 zmm0,zmmword ptr [r8]         ;load a values
        vmovdqa64 zmm1,zmmword ptr [r9]         ;load b values

        kmovb k1,edx                            ;k1 = opmask

        vpaddq zmm2{k1}{z},zmm0,zmm1            ;masked qword addition
        vmovdqa64 zmmword ptr [rcx],zmm2        ;save result

        vpsubq zmm2{k1}{z},zmm0,zmm1            ;masked qword subtraction
        vmovdqa64 zmmword ptr [rcx+64],zmm2     ;save result

        vpmullq zmm2{k1}{z},zmm0,zmm1           ;masked qword multiplication
        vmovdqa64 zmmword ptr [rcx+128],zmm2    ;save products (low 64-bits)

        vpsllvq zmm2{k1}{z},zmm0,zmm1           ;masked qword shift left
        vmovdqa64 zmmword ptr [rcx+192],zmm2    ;save result

        vpsravq zmm2{k1}{z},zmm0,zmm1           ;masked qword shift right
        vmovdqa64 zmmword ptr [rcx+256],zmm2    ;save result

        vzeroupper
        ret
MaskOpI64a_Aavx512 endp

;------------------------------------------------------------------------------
; void MaskOpI64b_Aavx512(ZmmVal c[5], uint8_t mask, const ZmmVal* a,
;   const ZmmVal* b1, const ZmmVal* b2);
;------------------------------------------------------------------------------

MaskOpI64b_Aavx512 proc
        vmovdqa64 zmm0,zmmword ptr [r8]         ;load a values
        vmovdqa64 zmm1,zmmword ptr [r9]         ;load b1 values
        mov rax,[rsp+40]                        ;rax = b2
        vmovdqa64 zmm2,zmmword ptr [rax]        ;load b2 values

        kmovb k1,edx                            ;k1 = opmask

        vpaddq zmm0{k1},zmm1,zmm2               ;masked qword addition
        vmovdqa64 zmmword ptr [rcx],zmm0        ;save result

        vpsubq zmm0{k1},zmm1,zmm2               ;masked qword subtraction
        vmovdqa64 zmmword ptr [rcx+64],zmm0     ;save result

        vpmullq zmm0{k1},zmm1,zmm2              ;masked qword multiplication
        vmovdqa64 zmmword ptr [rcx+128],zmm0    ;save products (low 64-bits)

        vpsllvq zmm0{k1},zmm1,zmm2              ;masked qword shift left
        vmovdqa64 zmmword ptr [rcx+192],zmm0    ;save result

        vpsravq zmm0{k1},zmm1,zmm2              ;masked qword shift right
        vmovdqa64 zmmword ptr [rcx+256],zmm0    ;save result

        vzeroupper
        ret
MaskOpI64b_Aavx512 endp

;------------------------------------------------------------------------------
; void MaskOpI64c_Aavx512(ZmmVal* c, const ZmmVal* a, int64_t x1, int64_t x2);
;------------------------------------------------------------------------------

MaskOpI64c_Aavx512 proc
        vmovdqa64 zmm0,zmmword ptr [rdx]        ;load a values
        vpbroadcastq zmm1,r8                    ;broadcast x1 to zmm1
        vpbroadcastq zmm2,r9                    ;broadcast x2 to zmm2

; c[i] = (a[i] >= x1) ? a[i] + x2 : a[i]
        vpcmpq k1,zmm0,zmm1,CMP_GE              ;k1 = a >= b mask
        vpaddq zmm0{k1},zmm0,zmm2               ;masked qword addition
        vmovdqa64 zmmword ptr [rcx],zmm0        ;save result

        vzeroupper
        ret
MaskOpI64c_Aavx512 endp
        end
