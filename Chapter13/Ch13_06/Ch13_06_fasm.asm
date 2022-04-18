;-------------------------------------------------
;               Ch13_06_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" bool CalcMeanU8_Aavx(double* mean_x, uint64_t* sum_x, const uint8_t* x,
;   size_t n);
;------------------------------------------------------------------------------

NSE     equ 64                              ;num_simd_elements

        .code
        extern g_NumElementsMax:qword

CalcMeanU8_Aavx proc
; Make sure n and x are valid
        test r9,r9                          ;is n == 0?
        jz BadArg                           ;jump if yes
        cmp r9,[g_NumElementsMax]           ;is n > g_NumElementsMax?
        ja BadArg                           ;jump if yes
        test r9,3fh                         ;is n even multiple of 64?
        jnz BadArg                          ;jump if no

        test r8,0fh                         ;is x aligned to 16b boundary?
        jnz BadArg                          ;jump if no

; Initialize
        vpxor xmm4,xmm4,xmm4                ;packed zero
        vpxor xmm5,xmm5,xmm5                ;packed sums (4 dwords)
        mov rax,-NSE                        ;initialize i

; Calculate sum of all pixels
Loop1:  add rax,NSE                         ;i += NSE
        cmp rax,r9                          ;is i >= n?
        jae @F                              ;jump if yes

        vpxor xmm3,xmm3,xmm3                ;loop packed sums (8 words)

        vmovdqa xmm0,xmmword ptr [r8+rax]   ;load block of 16 pixels
        vpunpcklbw xmm1,xmm0,xmm4           ;promote bytes to words
        vpunpckhbw xmm2,xmm0,xmm4
        vpaddw xmm3,xmm3,xmm1               ;update loop packed sums
        vpaddw xmm3,xmm3,xmm2

        vmovdqa xmm0,xmmword ptr [r8+rax+16]    ;load block of 16 pixels
        vpunpcklbw xmm1,xmm0,xmm4               ;promote bytes to words
        vpunpckhbw xmm2,xmm0,xmm4
        vpaddw xmm3,xmm3,xmm1                   ;update loop packed sums
        vpaddw xmm3,xmm3,xmm2

        vmovdqa xmm0,xmmword ptr [r8+rax+32]    ;load block of 16 pixels
        vpunpcklbw xmm1,xmm0,xmm4               ;promote bytes to words
        vpunpckhbw xmm2,xmm0,xmm4
        vpaddw xmm3,xmm3,xmm1                   ;update loop packed sums
        vpaddw xmm3,xmm3,xmm2

        vmovdqa xmm0,xmmword ptr [r8+rax+48]    ;load block of 16 pixels
        vpunpcklbw xmm1,xmm0,xmm4               ;promote bytes to words
        vpunpckhbw xmm2,xmm0,xmm4
        vpaddw xmm3,xmm3,xmm1                   ;update loop packed sums
        vpaddw xmm3,xmm3,xmm2

        vpunpcklwd xmm0,xmm3,xmm4               ;promote loop packed sums
        vpunpckhwd xmm1,xmm3,xmm4
        vpaddd xmm5,xmm5,xmm0                   ;update packed dword sums
        vpaddd xmm5,xmm5,xmm1

        jmp Loop1                               ;repeat until done

; Reduce packed sums (4 dwords) to single qword
@@:     vpextrd eax,xmm5,0                  ;rax = xmm5[31:0]
        vpextrd r10d,xmm5,1                 ;r10 = xmm5[63:32]
        add rax,r10                         ;update qword sum
        vpextrd r10d,xmm5,2                 ;r10 = xmm5[95:64]
        add rax,r10                         ;update qword sum
        vpextrd r10d,xmm5,3                 ;r10 = xmm5[127:96]
        add rax,r10                         ;update qword sum
        mov qword ptr [rdx],rax             ;save final qword sum

; Calculate mean
        vcvtsi2sd xmm0,xmm0,rax             ;convert sum to DPFP
        vcvtsi2sd xmm1,xmm1,r9              ;convert n to DPFP
        vdivsd xmm2,xmm0,xmm1               ;mean = sum / n
        vmovsd real8 ptr [rcx],xmm2         ;save mean

        mov eax,1                           ;set success return code
        ret

BadArg: xor eax,eax                         ;set error return code
        ret

CalcMeanU8_Aavx endp
        end
