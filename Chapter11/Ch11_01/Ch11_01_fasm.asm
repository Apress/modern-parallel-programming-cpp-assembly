;-------------------------------------------------
;               Ch11_01_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" int AddI32_A(int a, int b, int c);
;------------------------------------------------------------------------------

        .code
AddI32_A proc

; Calculate a + b + c
        add ecx,edx                         ;ecx = a + b
        add ecx,r8d                         ;ecx = a + b + c
        mov eax,ecx                         ;eax = final result

        ret                                 ;return to caller
AddI32_A endp

;------------------------------------------------------------------------------
; extern "C" long long SubI64_A(long long a, long long b, long long c);
;------------------------------------------------------------------------------

SubI64_A proc

; Calculate a - b - c
        sub rcx,rdx                         ;rcx = a - b
        sub rcx,r8                          ;rcx = a - b - c
        mov rax,rcx                         ;rax = final result

        ret                                 ;return to caller
SubI64_A endp
        end
