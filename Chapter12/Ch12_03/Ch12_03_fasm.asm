;-------------------------------------------------
;               Ch12_03_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" void CompareF32_Aavx(float a, float b, uint8_t* results);
;------------------------------------------------------------------------------

        .code
CompareF32_Aavx proc

; Set result flags based on compare status
        vcomiss xmm0,xmm1
        setp byte ptr [r8]                  ;RFLAGS.PF = 1 if unordered
        jnp @F
        xor al,al
        mov byte ptr [r8+1],al              ;set remaining elements in array
        mov byte ptr [r8+2],al              ;result[] to 0
        mov byte ptr [r8+3],al
        mov byte ptr [r8+4],al
        mov byte ptr [r8+5],al
        mov byte ptr [r8+6],al
        ret

@@:     setb byte ptr [r8+1]                ;set byte if a < b
        setbe byte ptr [r8+2]               ;set byte if a <= b
        sete byte ptr [r8+3]                ;set byte if a == b
        setne byte ptr [r8+4]               ;set byte if a != b
        seta byte ptr [r8+5]                ;set byte if a > b
        setae byte ptr [r8+6]               ;set byte if a >= b
        ret

CompareF32_Aavx endp
        end
