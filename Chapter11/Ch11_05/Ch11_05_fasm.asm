;-------------------------------------------------
;               Ch11_05_fasm.asm
;-------------------------------------------------

; Simple LUT (.const section data is read only)
                .const
PrimeNums       dword 2, 3, 5, 7, 11, 13, 17, 19, 23
                dword 29, 31, 37, 41, 43, 47, 53, 59
                dword 61, 67, 71, 73, 79, 83, 89, 97 

g_NumPrimes_A   dword ($ - PrimeNums) / sizeof dword
                public g_NumPrimes_A

; Data section (data is read/write)
                .data
g_SumPrimes_A   dword ?
                public g_SumPrimes_A

;------------------------------------------------------------------------------
; extern "C" int MemAddressing_A(int i, int* v1, int* v2, int* v3, int* v4);
;------------------------------------------------------------------------------

        .code
MemAddressing_A proc

; Make sure 'i' is valid
        cmp ecx,-1
        jle InvalidIndex                    ;jump if i <= -1
        cmp ecx,[g_NumPrimes_A]
        jge InvalidIndex                    ;jump if i >= g_NumPrimes_A

; Sign extend i for use in address calculations
        movsxd rcx,ecx                      ;sign extend i
        mov [rsp+8],rcx                     ;save copy of i (in rcx home area)

; Memory addressing - base register
        mov r11,offset PrimeNums            ;r11 = PrimeNums
        shl rcx,2                           ;rcx = i * 4
        add r11,rcx                         ;r11 = PrimeNums + i * 4
        mov eax,[r11]                       ;eax = PrimeNums[i]
        mov [rdx],eax                       ;save to v1

; Memory addressing - base register + index register
        mov r11,offset PrimeNums            ;r11 = PrimeNums
        mov rcx,[rsp+8]                     ;rcx = i
        shl rcx,2                           ;rcx = i * 4
        mov eax,[r11+rcx]                   ;eax = PrimeNums[i]
        mov [r8],eax                        ;save to v2

; Memory addressing - base register + index register * scale factor
        mov r11,offset PrimeNums            ;r11 = PrimeNums
        mov rcx,[rsp+8]                     ;rcx = i
        mov eax,[r11+rcx*4]                 ;eax = PrimeNums[i]
        mov [r9],eax                        ;save to v3

; Memory addressing - base register + index register * scale factor + disp
        mov r11,offset PrimeNums-42         ;r11 = PrimeNums - 42
        mov rcx,[rsp+8]                     ;rcx = i
        mov eax,[r11+rcx*4+42]              ;eax = PrimeNums[i]
        mov r10,[rsp+40]                    ;r10 = ptr to v4
        mov [r10],eax                       ;save to v4

; Mmeory addressing - RIP relative
        add [g_SumPrimes_A],eax             ;update sum
        mov eax,1                           ;set success return code
        ret

InvalidIndex:
        xor eax,eax                         ;set error return code
        ret

MemAddressing_A endp
        end
