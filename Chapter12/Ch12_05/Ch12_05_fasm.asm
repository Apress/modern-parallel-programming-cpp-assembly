;-------------------------------------------------
;               Ch12_05_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" bool CalcMeanF32_Aavx(float* mean, const float* x, size_t n);
;------------------------------------------------------------------------------

        .code
CalcMeanF32_Aavx proc

; Make sure n is valid
        cmp r8,2                            ;is n >= 2?
        jae @F                              ;jump if yes
        xor eax,eax                         ;set error return code
        ret

; Initialize
@@:     vxorps xmm0,xmm0,xmm0               ;sum = 0.0f
        mov rax,-1                          ;i = -1

; Sum the elements of x
Loop1:  inc rax                             ;i += 1
        cmp rax,r8                          ;is i >= n?
        jae CalcM                           ;jump if yes

        vaddss xmm0,xmm0,real4 ptr [rdx+rax*4]  ;sum += x[i]
        jmp Loop1

; Calculate and save the mean
CalcM:  vcvtsi2ss xmm1,xmm1,r8              ;convert n to SPFP
        vdivss xmm1,xmm0,xmm1               ;xmm2 = mean = sum / n
        vmovss real4 ptr [rcx],xmm1         ;save mean

        mov eax,1                           ;set success return code
        ret

CalcMeanF32_Aavx endp

;------------------------------------------------------------------------------
; extern "C" bool CalcStDevF32_Aavx(float* st_dev, const float* x, size_t n, float mean);
;------------------------------------------------------------------------------

CalcStDevF32_Aavx proc

; Make sure n is valid
        cmp r8,2                            ;is n >= 2?
        jae @F                              ;jump if yes
        xor eax,eax                         ;set error return code
        ret

; Initialize
@@:     vxorps xmm0,xmm0,xmm0               ;sum_squares = 0.0f
        mov rax,-1                          ;i = -1

; Sum the elements of x
Loop1:  inc rax                             ;i += 1
        cmp rax,r8                          ;is i >= n?
        jae CalcSD                          ;jump if yes

        vmovss xmm1,real4 ptr [rdx+rax*4]   ;xmm1 = x[i]
        vsubss xmm2,xmm1,xmm3               ;xmm2 = x[i] - mean
        vmulss xmm2,xmm2,xmm2               ;xmm2 = (x[i] - mean) ** 2
        vaddss xmm0,xmm0,xmm2               ;update sum_squares
        jmp Loop1

; Calculate and save standard deviation
CalcSD: dec r8                              ;r8 = n - 1
        vcvtsi2ss xmm1,xmm1,r8              ;convert n - 1 to SPFP
        vdivss xmm0,xmm0,xmm1               ;xmm0 = sum_squares / (n - 1)
        vsqrtss xmm0,xmm0,xmm0              ;xmm0 = st_dev
        vmovss real4 ptr [rcx],xmm0         ;save st_dev

        mov eax,1                           ;set success return code
        ret
CalcStDevF32_Aavx endp
        end
