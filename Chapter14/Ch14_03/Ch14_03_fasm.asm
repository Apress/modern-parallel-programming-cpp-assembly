;-------------------------------------------------
;               Ch14_03_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" bool CalcMeanF32_Aavx(float* mean, const float* x, size_t n);
;------------------------------------------------------------------------------

NSE     equ 8                               ;num_simd_elements

        .code
CalcMeanF32_Aavx proc

; Validate arguments
        cmp r8,2                            ;is n >= 2?
        jb BadArg                           ;jump if no
        test rdx,01fh                       ;is x 32b aligned?
        jnz BadArg                          ;jump if no

; Initialize
        mov rax,-NSE                        ;initialize i
        vxorps ymm5,ymm5,ymm5               ;packed sums = 0.0;

Loop1:  add rax,NSE                         ;i += NSE
        mov r10,r8                          ;r10 = n
        sub r10,rax                         ;r10 = n - i
        cmp r10,NSE                         ;is n - i >= NSE?
        jb @F                               ;jump if no

        vaddps ymm5,ymm5,ymmword ptr [rdx+rax*4]    ;add elements x[i:i+7]
        jmp Loop1                                   ;repeat loop until done

; Reduce packed sums to single value
@@:     vextractf128 xmm1,ymm5,1                ;extract upper 4 packed sums
        vaddps xmm2,xmm1,xmm5                   ;xmm2 = 4 packed sums
        vhaddps xmm3,xmm2,xmm2                  ;xmm3[63:0] = 2 packed sums
        vhaddps xmm5,xmm3,xmm3                  ;xmm5[31:0] = sum

Loop2:  cmp rax,r8                              ;is i >= n?
        jae @F                                  ;jump if yes
        vaddss xmm5,xmm5,real4 ptr[rdx+rax*4]   ;sum += x[i]
        inc rax                                 ;i += 1
        jmp Loop2                               ;repeat loop until done

; Calculate mean
@@:     vcvtsi2ss xmm0,xmm0,r8              ;convert n to SPFP
        vdivss xmm1,xmm5,xmm0               ;mean = sum / n
        vmovss real4 ptr [rcx],xmm1         ;save mean

        mov eax,1                           ;set success code
        vzeroupper                          ;clear upper YMM/ZMM bits
        ret

BadArg: xor eax,eax                         ;set error return code
        ret

CalcMeanF32_Aavx endp

;------------------------------------------------------------------------------
; extern "C" bool CalcStDevF32_Aavx(float* st_dev, const float* x, size_t n,
;   float mean);
;------------------------------------------------------------------------------

CalcStDevF32_Aavx proc
        cmp r8,2                            ;is n >= 2?
        jb BadArg                           ;jump if no
        test rdx,01fh                       ;is x 32b aligned?
        jnz BadArg                          ;jump if no

; Initialize
        mov rax,-NSE                        ;initialize i
        vxorps ymm5,ymm5,ymm5               ;packed sum_sqs = 0.0;

        vmovss real4 ptr [rsp+8],xmm3       ;save mean
        vbroadcastss ymm4,real4 ptr [rsp+8] ;ymm4 = packed mean

Loop1:  add rax,NSE                         ;i += NSE
        mov r10,r8                          ;r10 = n
        sub r10,rax                         ;r10 = n - i
        cmp r10,NSE                         ;is n - i >= NSE?
        jb @F                               ;jump if no

        vmovaps ymm0,ymmword ptr [rdx+rax*4]    ;load elements x[i:i+7]
        vsubps ymm1,ymm0,ymm4                   ;ymm1 = packed x[i] - mean
        vmulps ymm2,ymm1,ymm1                   ;ymm2 = packed (x[i] - mean) ** 2
        vaddps ymm5,ymm5,ymm2                   ;update packed sum_sqs
        jmp Loop1                               ;repeat loop until done

; Reduce packed sum_sqs to single value
@@:     vextractf128 xmm1,ymm5,1                ;extract upper 4 packed sum_sqs
        vaddps xmm2,xmm1,xmm5                   ;xmm2 = 4 packed sum_sqs
        vhaddps xmm3,xmm2,xmm2                  ;xmm3[63:0] = 2 sums_sqs
        vhaddps xmm5,xmm3,xmm3                  ;xmm5[31:0] = sum_sqs

Loop2:  cmp rax,r8                              ;is i >= n?
        jae @F                                  ;jump if yes
        vmovss xmm0,real4 ptr [rdx+rax*4]       ;load x[i]
        vsubss xmm1,xmm0,xmm4                   ;xmm1 = x[i] - mean
        vmulss xmm2,xmm1,xmm1                   ;xmm2 = (x[i] - mean) ** 2
        vaddss xmm5,xmm5,xmm2                   ;update sum_sqs
        inc rax                                 ;i += 1
        jmp Loop2                               ;repeat loop until done

; Calculate standard deviation
@@:     dec r8                              ;r8 = n - 1
        vcvtsi2ss xmm0,xmm0,r8              ;convert n - 1 to SPFP
        vdivss xmm1,xmm5,xmm0               ;var = sum_sqs / (n - 1)
        vsqrtss xmm2,xmm2,xmm1              ;sd = sqrt(var)
        vmovss real4 ptr [rcx],xmm2         ;save sd

        mov eax,1                           ;set success code
        vzeroupper                          ;clear upper YMM/ZMM bits
        ret

BadArg: xor eax,eax                         ;set error return code
        ret
CalcStDevF32_Aavx endp
        end
