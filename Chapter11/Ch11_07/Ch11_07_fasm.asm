;-------------------------------------------------
;               Ch11_07_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" int SignedMin1_A(int a, int b, int c);
;------------------------------------------------------------------------------

        .code
SignedMin1_A proc
        mov eax,ecx
        cmp eax,edx                         ;compare a and b
        jle @F                              ;jump if a <= b
        mov eax,edx                         ;eax = b

@@:     cmp eax,r8d                         ;compare min(a, b) and c
        jle @F
        mov eax,r8d                         ;eax = min(a, b, c)

@@:     ret
SignedMin1_A endp

;------------------------------------------------------------------------------
; extern "C" int SignedMin2_A(int a, int b, int c);
;------------------------------------------------------------------------------

SignedMin2_A proc
        cmp ecx,edx
        cmovg ecx,edx                       ;ecx = min(a, b)
        cmp ecx,r8d
        cmovg ecx,r8d                       ;ecx = min(a, b, c)
        mov eax,ecx
        ret
SignedMin2_A endp

;------------------------------------------------------------------------------
; extern "C" int SignedMax1_A(int a, int b, int c);
;------------------------------------------------------------------------------

SignedMax1_A proc
        mov eax,ecx
        cmp eax,edx                         ;compare a and b
        jge @F                              ;jump if a >= b
        mov eax,edx                         ;eax = b

@@:     cmp eax,r8d                         ;compare max(a, b) and c
        jge @F
        mov eax,r8d                         ;eax = max(a, b, c)

@@:     ret
SignedMax1_A endp

;------------------------------------------------------------------------------
; extern "C" int SignedMax2_A(int a, int b, int c);
;------------------------------------------------------------------------------

SignedMax2_A proc
        cmp ecx,edx
        cmovl ecx,edx                       ;ecx = max(a, b)
        cmp ecx,r8d
        cmovl ecx,r8d                       ;ecx = max(a, b, c)
        mov eax,ecx
        ret
SignedMax2_A endp
        end
