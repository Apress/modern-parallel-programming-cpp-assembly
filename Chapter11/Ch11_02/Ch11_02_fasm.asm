;-------------------------------------------------
;               Ch11_02_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" int32_t MulI32_A(int32_t a, int32_t b, int32_t c);
;------------------------------------------------------------------------------

        .code
MulI32_A proc

; Calculate a * b * c * 42
        imul ecx,edx                        ;ecx = a * b
        imul eax,r8d,42                     ;eax = c * 42
        imul eax,ecx                        ;eax = a * b * c * 42

        ret                                 ;return to caller
MulI32_A endp

;------------------------------------------------------------------------------
; extern "C" uint64_t MulU64_A(uint64_t a, uint64_t b, uint64_t c);
;------------------------------------------------------------------------------

MulU64_A proc

; Calculate a * b * c * 42
        mov rax,rcx                         ;rax = a
        mul rdx                             ;rdx:rax = a * b
        mov r10,rax                         ;r10 = a * b (low-order 64-bits)

        mov rax,42                          ;rax = 42
        mul r8                              ;rdx:rax = c * 42
        mul r10                             ;rdx:rax = a * b * c * 42

        ret                                 ;return to caller
MulU64_A endp
        end
