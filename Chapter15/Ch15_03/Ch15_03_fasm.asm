;-------------------------------------------------
;               Ch15_03_fasm.asm
;-------------------------------------------------

; The members of CD must match the corresponding structure
; that's declared in Ch15_03.h

CD               struct
PbSrc            qword ?
PbDes            qword ?
NumPixels        qword ?
NumClippedPixels qword ?
ThreshLo         byte ?
ThreshHi         byte ?
CD               ends

;------------------------------------------------------------------------------
; extern "C" void ClipPixels_Aavx2(ClipData* clip_data);
;------------------------------------------------------------------------------

NSE     equ 32                              ;num_simd_elements

        .code
ClipPixels_Aavx2 proc frame
        push rsi
        .pushreg rsi
        push rdi
        .pushreg rdi
        .endprolog

; Initialize
        xor r11,r11                             ;r11 = NumClippedPixels

        mov r8,qword ptr [rcx+CD.PbSrc]         ;r8 = PbSrc
        test r8,1fh
        jnz Done                                ;jump if PbSrc not 32b aligned

        mov r9,qword ptr [rcx+CD.PbDes]         ;r9 = PbDes
        test r9,1fh
        jnz Done                                ;jump if PbDes not 32b aligned

        mov r10,qword ptr [rcx+CD.NumPixels]    ;r10 = NumPixels
        test r10,r10
        jz Done                                 ;jump if NumPixels is zero

        mov rax,-NSE                                    ;initialize i
        vpbroadcastb ymm4,byte ptr [rcx+CD.ThreshLo]    ;packed ThreshLo
        vpbroadcastb ymm5,byte ptr [rcx+CD.ThreshHi]    ;packed ThreshHi

; Main for-loop
Loop1:  add rax,NSE                         ;i += NSE
        mov rdx,r10                         ;rdx = NumPixels
        sub rdx,rax                         ;rdx = NumPixels - i
        cmp rdx,NSE                         ;NumPixels - i < NSE?
        jb @F                               ;jump if yes

        vmovdqa ymm0,ymmword ptr [r8+rax]   ;load PbSrc[i:i+31]
        vpmaxub ymm1,ymm0,ymm4              ;clip to ThreshLo
        vpminub ymm2,ymm1,ymm5              ;clip to ThreshHi
        vmovdqa ymmword ptr [r9+rax],ymm2   ;save PbDes[i:i+31] (clipped pixels)

        vpcmpeqb ymm3,ymm2,ymm0             ;compare clipped to original
        vpmovmskb edx,ymm3                  ;edx = mask of non-clipped pixels
        not edx                             ;edx = mask of clipped pixels
        popcnt esi,edx                      ;esi = num clipped this iteration
        add r11,rsi                         ;update NumClippedPixels

        jmp Loop1                           ;repeat until done

@@:     cmp rax,r10                         ;is i >= NumPixels?
        jae Done                            ;jump if yes

        dec rax                                 ;adjust for Loop2
        mov sil,byte ptr [rcx+CD.ThreshLo]      ;sil = ThreshLo
        mov dil,byte ptr [rcx+CD.ThreshHi]      ;dil = ThreshHi

; Second for-loop for residual pixels (if any)
Loop2:  inc rax                             ;i += 1
        cmp rax,r10                         ;is i >= NumPixels
        jae Done                            ;jump if yes

        mov dl,byte ptr [r8+rax]            ;load next PbSrc[i]
        cmp dl,sil                          ;PbSrc[i] < ThreshLo?
        jb TH_LT                            ;jump is yes
        cmp dl,dil                          ;PbSrc[i] > ThreshHi?
        ja TH_GT                            ;jump if yes

        mov byte ptr [r9+rax],dl            ;save non-clipped pixel to PbDes[i]
        jmp Loop2

TH_LT:  inc r11                             ;NumClippedPixels += 1
        mov byte ptr [r9+rax],sil           ;save clipped pixel to PbDes[i]
        jmp Loop2

TH_GT:  inc r11                             ;NumClippedPixels += 1
        mov byte ptr [r9+rax],dil           ;save clipped pixel to PbDes[i]
        jmp Loop2

Done:   mov qword ptr [rcx+CD.NumClippedPixels],r11 ;save NumClippedPixels

        vzeroupper
        pop rdi
        pop rsi
        ret
ClipPixels_Aavx2 endp
        end
