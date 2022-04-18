;-------------------------------------------------
;               Ch11_06_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" int SumElementsI32_A(const int* x, size_t n);
;------------------------------------------------------------------------------

        .code
SumElementsI32_A proc

; Initialize sum to zero
        xor eax,eax                         ;sum = 0
        mov r10,-1                          ;i = -1

; Sum the elements of the array
Loop1:  inc r10                             ;i += 1
        cmp r10,rdx                         ;is i >= n?
        jae Done                            ;jump if i >= n

        add eax,[rcx+r10*4]                 ;sum += x[i]
        jmp Loop1                           ;perform next iteration

Done:   ret                                 ;return to caller

SumElementsI32_A endp
        end
