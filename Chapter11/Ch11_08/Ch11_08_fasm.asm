;-------------------------------------------------
;               Ch11_08_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
;extern "C" void CopyArrayI32_A(int32_t* b, const int32_t* a, size_t n);
;------------------------------------------------------------------------------

        .code
CopyArrayI32_A proc frame

; Save non-volatile registers on stack
        push rsi                            ;save rsi
        .pushreg rsi
        push rdi                            ;save rdi
        .pushreg rdi    
        .endprolog

; Copy the array
        mov rsi,rdx                         ;rsi = source array
        mov rdi,rcx                         ;rdi = destination array
        mov rcx,r8                          ;rcx = element count

        rep movsd                           ;copy the array

; Restore non-volatile registers and return
        pop rdi                             ;restore rdi
        pop rsi                             ;restore rsi
        ret
CopyArrayI32_A endp

;------------------------------------------------------------------------------
; extern "C" void FillArrayI32_A(const int32_t* a, int32_t val, size_t n);
;------------------------------------------------------------------------------

FillArrayI32_A proc frame

; Save non-volatile registers on stack
        push rdi                            ;save rdi
        .pushreg rdi    
        .endprolog

; Fill the array
        mov rdi,rcx                         ;rdi = destination array
        mov eax,edx                         ;eax = fill value                         
        mov rcx,r8                          ;rcx = element count

        rep stosd                           ;fill the array

; Restore non-volatile registers and return
        pop rdi                             ;restore rdi
        ret
FillArrayI32_A endp
        end
