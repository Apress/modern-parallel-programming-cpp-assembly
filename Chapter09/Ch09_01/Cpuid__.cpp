//------------------------------------------------
//               Cpuid__.cpp
//------------------------------------------------

#include <string>
#include <cassert>
#include <immintrin.h>
#include "Cpuid__.h"

#if defined(_MSC_VER)
#include <intrin.h>
#elif defined (__GNUG__)
#include <cpuid.h>
#include <x86intrin.h>
#else
#error Unknown target in Cpuid__.cpp
#endif

uint32_t Cpuid__(uint32_t r_eax, uint32_t r_ecx, CpuidRegs* r_out)
{
#if defined(_MSC_VER)
    int cpuid_info[4];

    cpuid_info[0] = cpuid_info[1] = cpuid_info[2] = cpuid_info[3] = 0;

    __cpuidex(cpuid_info, r_eax, r_ecx);
#endif

#if defined (__GNUG__)
    uint32_t cpuid_info[4];

    cpuid_info[0] = cpuid_info[1] = cpuid_info[2] = cpuid_info[3] = 0;

    __get_cpuid_count(r_eax, r_ecx, &cpuid_info[0], &cpuid_info[1],
                                    &cpuid_info[2], &cpuid_info[3]); 
#endif

    r_out->EAX = cpuid_info[0];
    r_out->EBX = cpuid_info[1];
    r_out->ECX = cpuid_info[2];
    r_out->EDX = cpuid_info[3];

    uint32_t rc = cpuid_info[0] | cpuid_info[1] | cpuid_info[2] | cpuid_info[3];
    return rc;
}

void Xgetbv__(uint32_t r_ecx, uint32_t* r_eax, uint32_t* r_edx)
{
    uint64_t x = _xgetbv(r_ecx);

    *r_eax = (uint32_t)(x & 0xFFFFFFFF);
    *r_edx = (uint32_t)((x & 0xFFFFFFFF00000000) >> 32);
}
