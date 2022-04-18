//------------------------------------------------
//               Ch09_01.cpp
//------------------------------------------------

#include <iostream>
#include <string>
#include "CpuidInfo.h"

static void DisplayProcessorInfo(const CpuidInfo& ci);
static void DisplayCacheInfo(const CpuidInfo& ci);
static void DisplayFeatureFlags(const CpuidInfo& ci);

int main()
{
    CpuidInfo ci;
    ci.LoadInfo();

    DisplayProcessorInfo(ci);
    DisplayCacheInfo(ci);
    DisplayFeatureFlags(ci);
    return 0;
}

static void DisplayProcessorInfo(const CpuidInfo& ci)
{
    const char nl = '\n';
    std::cout << "\n----- Processor Info  -----" << nl;
    std::cout << "Processor vendor: " << ci.GetProcessorVendor() << nl;
    std::cout << "Processor brand:  " << ci.GetProcessorBrand() << nl;
}

static void DisplayCacheInfo(const CpuidInfo& ci)
{
    const char nl = '\n';
    const std::vector<CpuidInfo::CacheInfo>& cache_info = ci.GetCacheInfo();

    std::cout << "\n----- Cache Info  -----" << nl;

    for (const CpuidInfo::CacheInfo& x : cache_info)
    {
        uint32_t cache_size = x.GetSize();
        uint32_t cache_size_kb = cache_size / 1024;

        std::cout << "Cache L" << x.GetLevel() << ": ";
        std::cout << cache_size_kb << " KB - ";
        std::cout << x.GetTypeString() << nl;
    }
}

static void DisplayFeatureFlags(const CpuidInfo& ci)
{
    const char nl = '\n';

    std::cout << "\n----- Processor CPUID Feature Flags -----" << nl;
    std::cout << "FMA:                 " << ci.GetFF(CpuidInfo::FF::FMA) << nl;
    std::cout << "AVX:                 " << ci.GetFF(CpuidInfo::FF::AVX) << nl;
    std::cout << "AVX2:                " << ci.GetFF(CpuidInfo::FF::AVX2) << nl;
    std::cout << "AVX512F:             " << ci.GetFF(CpuidInfo::FF::AVX512F) << nl;
    std::cout << "AVX512CD:            " << ci.GetFF(CpuidInfo::FF::AVX512CD) << nl;
    std::cout << "AVX512DQ:            " << ci.GetFF(CpuidInfo::FF::AVX512DQ) << nl;
    std::cout << "AVX512BW:            " << ci.GetFF(CpuidInfo::FF::AVX512BW) << nl;
    std::cout << "AVX512VL:            " << ci.GetFF(CpuidInfo::FF::AVX512VL) << nl;
    std::cout << "AVX512_IFMA:         " << ci.GetFF(CpuidInfo::FF::AVX512_IFMA) << nl;
    std::cout << "AVX512_VBMI:         " << ci.GetFF(CpuidInfo::FF::AVX512_VBMI) << nl;
    std::cout << "AVX512_VNNI:         " << ci.GetFF(CpuidInfo::FF::AVX512_VNNI) << nl;
    std::cout << "AVX512_VPOPCNTDQ:    " << ci.GetFF(CpuidInfo::FF::AVX512_VPOPCNTDQ) << nl;
    std::cout << "AVX512_VBMI2:        " << ci.GetFF(CpuidInfo::FF::AVX512_VBMI2) << nl;
    std::cout << "AVX512_BITALG:       " << ci.GetFF(CpuidInfo::FF::AVX512_BITALG) << nl;
    std::cout << "AVX512_BF16:         " << ci.GetFF(CpuidInfo::FF::AVX512_BF16) << nl;
    std::cout << "AVX512_VP2INTERSECT: " << ci.GetFF(CpuidInfo::FF::AVX512_VP2INTERSECT) << nl;
    std::cout << "AVX512_FP16:         " << ci.GetFF(CpuidInfo::FF::AVX512_FP16) << nl;
}
