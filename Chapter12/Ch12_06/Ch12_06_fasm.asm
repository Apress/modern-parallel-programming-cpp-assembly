;-------------------------------------------------
;               Ch12_06_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" int64_t SumIntegers_A(int8_t a, int16_t b, int32_t c, int64_t d,
;   int8_t e, int16_t f, int32_t g, int64_t h);
;------------------------------------------------------------------------------

; Named expressions for constant values:
;
; RBP_RA        = number of bytes between RBP and return address on stack
; STK_LOCAL     = size of local stack space

RBP_RA = 24
STK_LOCAL = 16

        .code
SumIntegers_A proc frame

; Function prologue
        push rbp                            ;save caller's rbp register
        .pushreg rbp
        sub rsp,STK_LOCAL                   ;allocate local stack space
        .allocstack STK_LOCAL
        mov rbp,rsp                         ;set frame pointer
        .setframe rbp,0
        .endprolog                          ;mark end of prologe

; Save argument registers to home area (optional)
        mov [rbp+RBP_RA+8],rcx
        mov [rbp+RBP_RA+16],rdx
        mov [rbp+RBP_RA+24],r8
        mov [rbp+RBP_RA+32],r9

; Calculate a + b + c + d
        movsx rcx,cl                        ;rcx = a
        movsx rdx,dx                        ;rdx = b
        movsxd r8,r8d                       ;r8 = c;
        add rcx,rdx                         ;rcx = a + b
        add r8,r9                           ;r8 = c + d
        add r8,rcx                          ;r8 = a + b + c + d
        mov [rbp],r8                        ;save a + b + c + d on stack

; Calculate e + f + g + h
        movsx rcx,byte ptr [rbp+RBP_RA+40]  ;rcx = e
        movsx rdx,word ptr [rbp+RBP_RA+48]  ;rdx = f
        movsxd r8,dword ptr [rbp+RBP_RA+56] ;r8 = g
        add rcx,rdx                         ;rcx = e + f
        add r8,qword ptr [rbp+RBP_RA+64]    ;r8 = g + h
        add r8,rcx                          ;r8 = e + f + g + h

; Compute final sum
        mov rax,[rbp]                       ;rax = a + b + c + d
        add rax,r8                          ;rax = final sum

; Function epilogue
        add rsp,16                          ;release local stack space
        pop rbp                             ;restore caller's rbp register
        ret

SumIntegers_A endp
        end
