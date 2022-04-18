//------------------------------------------------
//               Cpuid__.h
//------------------------------------------------

#pragma once
#include <cstdint>

struct CpuidRegs
{
    uint32_t EAX;
    uint32_t EBX;
    uint32_t ECX;
    uint32_t EDX;
};

// Cpuid__.cpp
extern uint32_t Cpuid__(uint32_t r_eax, uint32_t r_ecx, CpuidRegs* r_out);
extern void Xgetbv__(uint32_t r_ecx, uint32_t* r_eax, uint32_t* r_edx);
