;-------------------------------------------------
;               Ch01_01_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" void CalcZ_Aavx(float* z, const float* x, const float* x, size_t n);
;------------------------------------------------------------------------------

NSE     equ 8                                   ;num_simd_elements

        .code
CalcZ_Aavx proc
        xor rax,rax                             ;i = 0;

Loop1:  mov r10,r9                              ;r10 = n
        sub r10,rax                             ;r10 = n - i
        cmp r10,NSE                             ;is n - i < NSE?
        jb Loop2                                ;jump if yes

; Calculate z[i:i+7] = x[i:i+7] + y[i:i+7]
        vmovups ymm0,ymmword ptr [rdx+rax*4]    ;ymm0 = x[i:i+7]
        vmovups ymm1,ymmword ptr [r8+rax*4]     ;ymm1 = y[i:i+7]
        vaddps ymm2,ymm0,ymm1                   ;z[i:i+7] = x[i:i+7] + y[i:i+7]
        vmovups ymmword ptr [rcx+rax*4],ymm2    ;save z[i:i+7]

        add rax,NSE                             ;i += NSE
        jmp Loop1                               ;repeat Loop1 until done

Loop2:  cmp rax,r9                              ;is i >= n?
        jae Done                                ;jump if yes

; Calculate z[i] = x[i] + y[i] for remaining elements
        vmovss xmm0,real4 ptr [rdx+rax*4]       ;xmm0 = x[i]
        vmovss xmm1,real4 ptr [r8+rax*4]        ;xmm1 = y[i]
        vaddss xmm2,xmm0,xmm1                   ;z[i] = x[i] + y[i]
        vmovss real4 ptr [rcx+rax*4],xmm2       ;save z[i]

        inc rax                                 ;i += 1
        jmp Loop2                               ;repeat Loop2 until done

Done:   vzeroupper                              ;clear upper bits of ymm regs
        ret                                     ;return to caller
CalcZ_Aavx endp
        end
