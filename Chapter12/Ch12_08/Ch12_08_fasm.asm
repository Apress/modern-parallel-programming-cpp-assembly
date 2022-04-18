;-------------------------------------------------
;               Ch12_08_fasm.asm
;-------------------------------------------------

;------------------------------------------------------------------------------
; extern "C" bool CalcConeAreaVol_A(const double* r, const double* h, int n,
; double* sa_cone, double* vol_cone);
;------------------------------------------------------------------------------

; Named expressions for constant values
;
; NUM_PUSHREG   = number of prolog non-volatile register pushes
; STK_LOCAL1    = size in bytes of STK_LOCAL1 area (see figure in text)
; STK_LOCAL2    = size in bytes of STK_LOCAL2 area (see figure in text)
; STK_PAD       = extra bytes (0 or 8) needed to 16-byte align RSP
; STK_TOTAL     = total size in bytes of local stack
; RBP_RA        = number of bytes between RBP and ret addr on stack

NUM_PUSHREG     = 7
STK_LOCAL1      = 16
STK_LOCAL2      = 64
STK_PAD         = ((NUM_PUSHREG AND 1) XOR 1) * 8
STK_TOTAL       = STK_LOCAL1 + STK_LOCAL2 + STK_PAD
RBP_RA          = NUM_PUSHREG * 8 + STK_LOCAL1 + STK_PAD

            .const
r8_3p0      real8 3.0
r8_pi       real8 3.14159265358979323846

        .code
CalcConeAreaVol_A proc frame

; Save non-volatile general-purpose registers
        push rbp
        .pushreg rbp
        push rbx
        .pushreg rbx
        push rsi
        .pushreg rsi
        push r12
        .pushreg r12
        push r13
        .pushreg r13
        push r14
        .pushreg r14
        push r15
        .pushreg r15

; Allocate local stack space and initialize frame pointer
        sub rsp,STK_TOTAL                   ;allocate local stack space
        .allocstack STK_TOTAL
        lea rbp,[rsp+STK_LOCAL2]            ;rbp = stack frame pointer
        .setframe rbp,STK_LOCAL2

; Save non-volatile registers XMM12 - XMM15. Note that STK_LOCAL2 must
; be greater than or equal to the number of XMM register saves times 16.
        vmovdqa xmmword ptr [rbp-STK_LOCAL2+48],xmm12
       .savexmm128 xmm12,48
        vmovdqa xmmword ptr [rbp-STK_LOCAL2+32],xmm13
       .savexmm128 xmm13,32
        vmovdqa xmmword ptr [rbp-STK_LOCAL2+16],xmm14
       .savexmm128 xmm14,16
        vmovdqa xmmword ptr [rbp-STK_LOCAL2],xmm15
       .savexmm128 xmm15,0
        .endprolog

; Access local variables on the stack (demonstration only)
        mov qword ptr [rbp],-1              ;LocalVar1A = -1
        mov qword ptr [rbp+8],-2            ;LocalVar1B = -2

; Initialize the processing loop variables. Note that many of the
; register initializations below are performed merely to illustrate
; use of the non-volatile GP and XMM registers.
        mov esi,r8d                         ;esi = n
        test esi,esi                        ;is n > 0?
        jg @F                               ;jump if n > 0

        xor eax,eax                         ;set error return code
        jmp Done

@@:     mov rbx,-8                          ;rbx = offset to array elements
        mov r12,rcx                         ;r12 = ptr to r
        mov r13,rdx                         ;r13 = ptr to h
        mov r14,r9                          ;r14 = ptr to sa_cone
        mov r15,[rbp+RBP_RA+40]             ;r15 = ptr to vol_cone
        vmovsd xmm14,real8 ptr [r8_pi]      ;xmm14 = pi
        vmovsd xmm15,real8 ptr [r8_3p0]     ;xmm15 = 3.0

; Calculate cone surface areas and volumes
; sa = pi * r * (r + sqrt(r * r + h * h))
; vol = pi * r * r * h / 3
@@:     add rbx,8                           ;rbx = offset to next elements
        vmovsd xmm0,real8 ptr [r12+rbx]     ;xmm0 = r
        vmovsd xmm1,real8 ptr [r13+rbx]     ;xmm1 = h
        vmovsd xmm12,xmm12,xmm0             ;xmm12 = r
        vmovsd xmm13,xmm13,xmm1             ;xmm13 = h

        vmulsd xmm0,xmm0,xmm0         ;xmm0 = r * r
        vmulsd xmm1,xmm1,xmm1         ;xmm1 = h * h
        vaddsd xmm0,xmm0,xmm1         ;xmm0 = r * r + h * h

        vsqrtsd xmm0,xmm0,xmm0        ;xmm0 = sqrt(r * r + h * h)
        vaddsd xmm0,xmm0,xmm12        ;xmm0 = r + sqrt(r * r + h * h)
        vmulsd xmm0,xmm0,xmm12        ;xmm0 = r * (r + sqrt(r * r + h * h))
        vmulsd xmm0,xmm0,xmm14        ;xmm0 = pi * r * (r + sqrt(r * r + h * h))

        vmulsd xmm12,xmm12,xmm12       ;xmm12 = r * r
        vmulsd xmm13,xmm13,xmm14       ;xmm13 = h * pi
        vmulsd xmm13,xmm13,xmm12       ;xmm13 = pi * r * r * h
        vdivsd xmm13,xmm13,xmm15       ;xmm13 = pi * r * r * h / 3

        vmovsd real8 ptr [r14+rbx],xmm0     ;save surface area
        vmovsd real8 ptr [r15+rbx],xmm13    ;save volume

        dec esi                             ;update counter
        jnz @B                              ;repeat until done

        mov eax,1                           ;set success return code

; Restore non-volatile XMM registers
Done:   vmovdqa xmm12,xmmword ptr [rbp-STK_LOCAL2+48]
        vmovdqa xmm13,xmmword ptr [rbp-STK_LOCAL2+32]
        vmovdqa xmm14,xmmword ptr [rbp-STK_LOCAL2+16]
        vmovdqa xmm15,xmmword ptr [rbp-STK_LOCAL2]

; Restore non-volatile general-purpose registers
        lea rsp,[rbp+STK_LOCAL1+STK_PAD]    ;restore rsp
        pop r15
        pop r14
        pop r13
        pop r12
        pop rsi
        pop rbx
        pop rbp
        ret
CalcConeAreaVol_A endp
        end
