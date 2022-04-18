;-------------------------------------------------
;               Ch11_03_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern int32_t DivI32_A(int32_t a, int32_t b, int32_t* quo, int32_t* rem);
;------------------------------------------------------------------------------

        .code
DivI32_A proc

; Make sure divisor b is not zero
        or edx,edx                          ;bitwise OR (sets status flags)
        jz InvalidDivisor                   ;jump if b is zero

; Calculate quotient and remainder of a / b
        mov eax,ecx                         ;eax = a
        mov r10d,edx                        ;r10d = b
        cdq                                 ;edx:eax = 64-bit signed dividend
        idiv r10d                           ;eax = quotient, edx = remainder

; Save results
        mov [r8],eax                        ;save quotient
        mov [r9],edx                        ;save remainder 
        mov eax,1                           ;set success return code
        ret

InvalidDivisor:
        xor eax,eax                         ;set error return code (eax = 0)
        ret
DivI32_A endp

;------------------------------------------------------------------------------
; extern int32_t DivU64_A(uint64_t a, uint64_t b, uint64_t* quo, uint64_t* rem);
;------------------------------------------------------------------------------

DivU64_A proc

; Make sure divisor b is not zero
        or rdx,rdx                          ;bitwise OR (sets status flags)
        jz InvalidDivisor                   ;jump if b is zero

; Calculate quotient and remainder of a / b
        mov r10,rdx                         ;r10 = b
        mov rax,rcx                         ;rax = a
        xor rdx,rdx                         ;rdx:rax = 128-bit unsigned dividend
        div r10                             ;rax = quotient, rdx = remainder

; Save results
        mov [r8],rax                        ;save quotient
        mov [r9],rdx                        ;save remainder 
        mov eax,1                           ;set success return code
        ret

InvalidDivisor:
        xor eax,eax                         ;set error return code (eax = 0)
        ret

DivU64_A endp
        end
