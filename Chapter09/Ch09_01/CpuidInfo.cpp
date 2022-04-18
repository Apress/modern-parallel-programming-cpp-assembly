//------------------------------------------------
//               CpuidInfo.cpp
//------------------------------------------------

#include <string>
#include <cstring>
#include <vector>
#include "CpuidInfo.h"

void CpuidInfo::LoadInfo(void)
{
    // Note: LoadInfo0 must be called first
    LoadInfo0();
    LoadInfo1();
    LoadInfo2();
    LoadInfo3();
    LoadInfo4();
    LoadInfo5();
}

void CpuidInfo::LoadInfo0(void)
{
    CpuidRegs r1;

    // Perform required initializations
    Init();

    // Get MaxEax and VendorID
    Cpuid__(0, 0, &r1);
    m_MaxEax = r1.EAX;

    uint32_t* p = (uint32_t*)m_VendorId;
    p[0] = r1.EBX;
    p[1] = r1.EDX;
    p[2] = r1.ECX;

    m_VendorId[sizeof(m_VendorId) - 1] = '\0';

    // Get MaxEaxExt
    Cpuid__(0x80000000, 0, &r1);
    m_MaxEaxExt = r1.EAX;

    // Initialize processor brand string
    InitProcessorBrand();
}

void CpuidInfo::LoadInfo1(void)
{
    CpuidRegs r;

    if (m_MaxEax < 1)
        return;

    Cpuid__(1, 0, &r);

    //
    // Decode r.ECX flags
    //

    // CPUID.(EAX=01H, ECX=00H):ECX.SSE3[bit 0]
    if (r.ECX & (0x1 << 0))
        m_FeatureFlags |= (uint64_t)FF::SSE3;

    // CPUID.(EAX=01H, ECX=00H):ECX.PCLMULQDQ[bit 1]
    if (r.ECX & (0x1 << 1))
        m_FeatureFlags |= (uint64_t)FF::PCLMULQDQ;

    // CPUID.(EAX=01H, ECX=00H):ECX.SSSE3[bit 9]
    if (r.ECX & (0x1 << 9))
        m_FeatureFlags |= (uint64_t)FF::SSSE3;

    // CPUID.(EAX=01H, ECX=00H):ECX.SSE4.1[bit 19]
    if (r.ECX & (0x1 << 19))
        m_FeatureFlags |= (uint64_t)FF::SSE4_1;

    // CPUID.(EAX=01H, ECX=00H):ECX.SSE4.2[bit 20]
    if (r.ECX & (0x1 << 20))
        m_FeatureFlags |= (uint64_t)FF::SSE4_2;

    // CPUID.(EAX=01H, ECX=00H):ECX.MOVBE[bit 22]
    if (r.ECX & (0x1 << 22))
        m_FeatureFlags |= (uint64_t)FF::MOVBE;

    // CPUID.(EAX=01H, ECX=00H):ECX.POPCNT[bit 23]
    if (r.ECX & (0x1 << 23))
        m_FeatureFlags |= (uint64_t)FF::POPCNT;

    // CPUID.(EAX=01H, ECX=00H):ECX.AESNI[bit 25]
    if (r.ECX & (0x1 << 25))
        m_FeatureFlags |= (uint64_t)FF::AESNI;

    // CPUID.(EAX=01H, ECX=00H):ECX.RDRAND[bit 30]
    if (r.ECX & (0x1 << 30))
        m_FeatureFlags |= (uint64_t)FF::RDRAND;

    //
    // Decode r.RDX flags
    //

    // CPUID.(EAX=01H, ECX=00H):EDX.MMX[bit 23]
    if (r.EDX & (0x1 << 23))
        m_FeatureFlags |= (uint64_t)FF::MMX;

    // CPUID.(EAX=01H, ECX=00H):EDX.FXSR[bit 24]
    if (r.EDX & (0x1 << 24))
        m_FeatureFlags |= (uint64_t)FF::FXSR;

    // CPUID.(EAX=01H, ECX=00H):EDX.SSE[bit 25]
    if (r.EDX & (0x1 << 25))
        m_FeatureFlags |= (uint64_t)FF::SSE;

    // CPUID.(EAX=01H, ECX=00H):EDX.SSE2[bit 26]
    if (r.EDX & (0x1 << 26))
        m_FeatureFlags |= (uint64_t)FF::SSE2;
}

void CpuidInfo::LoadInfo2(void)
{
    CpuidRegs   r;

    if (m_MaxEax < 7)
        return;

    Cpuid__(7, 0, &r);

    //
    // Decode EBX flags
    //

    // CPUID.(EAX=07H, ECX=00H):EBX.BMI1[bit 3]
    if (r.EBX & (0x1 << 3))
        m_FeatureFlags |= (uint64_t)FF::BMI1;

    // CPUID.(EAX=07H, ECX=00H):EBX.BMI2[bit 8]
    if (r.EBX & (0x1 << 8))
        m_FeatureFlags |= (uint64_t)FF::BMI2;

    // CPUID.(EAX=07H, ECX=00H):EBX.ERMSB[bit 9]
    // ERMSB = Enhanced REP MOVSB/STOSB
    if (r.EBX & (0x1 << 9))
        m_FeatureFlags |= (uint64_t)FF::ERMSB;

    // CPUID.(EAX=07H, ECX=00H):EBX.RDSEED[bit 18]
    if (r.EBX & (0x1 << 18))
        m_FeatureFlags |= (uint64_t)FF::RDSEED;

    // CPUID.(EAX=07H, ECX=00H):EBX.ADX[bit 19]
    if (r.EBX & (0x1 << 19))
        m_FeatureFlags |= (uint64_t)FF::ADX;

    // CPUID.(EAX=07H, ECX=00H):EBX.CLWB[bit 24]
    if (r.EBX & (0x1 << 24))
        m_FeatureFlags |= (uint64_t)FF::CLWB;

    //
    // Decode ECX flags
    //

    // CPUID.(EAX=07H, ECX=00H):ECX.PREFETCHWT1[bit 0]
    if (r.ECX & (0x1 << 0))
        m_FeatureFlags |= (uint64_t)FF::PREFETCHWT1;

    // CPUID.(EAX=07H, ECX=00H):ECX.GFNI[bit 8]
    if (r.ECX & (0x1 << 8))
        m_FeatureFlags |= (uint64_t)FF::GFNI;
}

void CpuidInfo::LoadInfo3(void)
{
    CpuidRegs r;

    if (m_MaxEaxExt < 0x80000001)
        return;

    Cpuid__(0x80000001, 0, &r);

    // CPUID.(EAX=80000001H, ECX=00H):ECX.LZCNT[bit 5]
    if (r.ECX & (0x1 << 5))
        m_FeatureFlags |= (uint64_t)FF::LZCNT;

    // CPUID.(EAX=80000001H, ECX=00H):ECX.PREFETCHW[bit 8]
    if (r.ECX & (0x1 << 8))
        m_FeatureFlags |= (uint64_t)FF::PREFETCHW;
}

void CpuidInfo::LoadInfo4(void)
{
    CpuidRegs r_eax01h;
    CpuidRegs r_eax07h;
    CpuidRegs r_eax07h_ecx01h;

    if (m_MaxEax < 7)
        return;

    Cpuid__(1, 0, &r_eax01h);
    Cpuid__(7, 0, &r_eax07h);
    Cpuid__(7, 1, &r_eax07h_ecx01h);

    // Test CPUID.(EAX=01H, ECX=00H):ECX.OSXSAVE[bit 27] to verify use of XGETBV
    m_OsXsave = (r_eax01h.ECX & (0x1 << 27)) ? true : false;

    if (m_OsXsave)
    {
        // Use XGETBV to obtain following information
        // AVX state is enabled by OS if (XCR0[2:1] == '11b') is true
        // AVX-512 state is enabled by OS if (XCR0[7:5] == '111b') is true

        uint32_t xgetbv_eax, xgetbv_edx;

        Xgetbv__(0, &xgetbv_eax, &xgetbv_edx);
        m_OsAvxState = (((xgetbv_eax >> 1) & 0x03) == 0x03) ? true : false;

        if (m_OsAvxState)
        {
            // CPUID.(EAX=01H, ECX=00H):ECX.AVX[bit 28]
            if (r_eax01h.ECX & (0x1 << 28))
            {
                m_FeatureFlags |= (uint64_t)FF::AVX;

                //
                // Decode ECX flags
                //

                // CPUID.(EAX=07H, ECX=00H):EBX.AVX2[bit 5]
                if (r_eax07h.EBX & (0x1 << 5))
                    m_FeatureFlags |= (uint64_t)FF::AVX2;

                // CPUID.(EAX=07H, ECX=00H):ECX.VAES[bit 9]
                if (r_eax07h.ECX & (0x1 << 9))
                    m_FeatureFlags |= (uint64_t)FF::VAES;

                // CPUID.(EAX=07H, ECX=00H):ECX.VPCLMULQDQ[bit 10]
                if (r_eax07h.ECX & (0x1 << 10))
                    m_FeatureFlags |= (uint64_t)FF::VPCLMULQDQ;

                // CPUID.(EAX=01H, ECX=00H):ECX.FMA[bit 12]
                if (r_eax01h.ECX & (0x1 << 12))
                    m_FeatureFlags |= (uint64_t)FF::FMA;

                // CPUID.(EAX=01H, ECX=00H):ECX.F16C[bit 29]
                if (r_eax01h.ECX & (0x1 << 29))
                    m_FeatureFlags |= (uint64_t)FF::F16C;

                //
                // Decode EAX flags (subleaf 1)
                //

                // CPUID.(EAX=07H, ECX=01H):EAX.AVX_VNNI[bit 4]
                if (r_eax07h_ecx01h.EAX & (0x1 << 4))
                    m_FeatureFlags |= (uint64_t)FF::AVX_VNNI;

                m_OsAvx512State = (((xgetbv_eax >> 5) & 0x07) == 0x07) ? true : false;

                if (m_OsAvx512State)
                {
                    // CPUID.(EAX=07H, ECX=00H):EBX.AVX512F[bit 16]
                    if (r_eax07h.EBX & (0x1 << 16))
                    {
                        m_FeatureFlags |= (uint64_t)FF::AVX512F;

                        //
                        // Decode EBX flags
                        //

                        // CPUID.(EAX=07H, ECX=00H):EBX.AVX512DQ[bit 17]
                        if (r_eax07h.EBX & (0x1 << 17))
                            m_FeatureFlags |= (uint64_t)FF::AVX512DQ;

                        // CPUID.(EAX=07H, ECX=00H):EBX.AVX512_IFMA[bit 21]
                        if (r_eax07h.EBX & (0x1 << 21))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_IFMA;

                        // CPUID.(EAX=07H, ECX=00H):EBX.AVX512PF[bit 26]
                        if (r_eax07h.EBX & (0x1 << 26))
                            m_FeatureFlags |= (uint64_t)FF::AVX512PF;

                        // CPUID.(EAX=07H, ECX=00H):EBX.AVX512ER[bit 27]
                        if (r_eax07h.EBX & (0x1 << 27))
                            m_FeatureFlags |= (uint64_t)FF::AVX512ER;

                        // CPUID.(EAX=07H, ECX=00H):EBX.AVX512CD[bit 28]
                        if (r_eax07h.EBX & (0x1 << 28))
                            m_FeatureFlags |= (uint64_t)FF::AVX512CD;

                        // CPUID.(EAX=07H, ECX=00H):EBX.AVX512BW[bit 30]
                        if (r_eax07h.EBX & (0x1 << 30))
                            m_FeatureFlags |= (uint64_t)FF::AVX512BW;

                        // CPUID.(EAX=07H, ECX=00H):EBX.AVX512VL[bit 31]
                        if (r_eax07h.EBX & (0x1 << 31))
                            m_FeatureFlags |= (uint64_t)FF::AVX512VL;

                        //
                        // Decode ECX flags
                        //

                        // CPUID.(EAX=07H, ECX=00H):ECX.AVX512_VBMI[bit 1]
                        if (r_eax07h.ECX & (0x1 << 1))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_VBMI;

                        // CPUID.(EAX=07H, ECX=00H):ECX.AVX512_VBMI2[bit 6]
                        if (r_eax07h.ECX & (0x1 << 6))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_VBMI2;

                        // CPUID.(EAX=07H, ECX=00H):ECX.AVX512_VNNI[bit 11]
                        if (r_eax07h.ECX & (0x1 << 11))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_VNNI;

                        // CPUID.(EAX=07H, ECX=00H):ECX.AVX512_BITALG[bit 12]
                        if (r_eax07h.ECX & (0x1 << 12))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_BITALG;

                        // CPUID.(EAX=07H, ECX=00H):ECX.AVX512_VPOPCNTDQ[bit 14]
                        if (r_eax07h.ECX & (0x1 << 14))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_VPOPCNTDQ;

                        //
                        // Decode EDX flags
                        //

                        // CPUID.(EAX=07H, ECX=00H):EDX.AVX512_4FMAPS[bit 2]
                        if (r_eax07h.EDX & (0x1 << 2))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_4FMAPS;

                        // CPUID.(EAX=07H, ECX=00H):EDX.AVX512_4VNNIW[bit 3]
                        if (r_eax07h.EDX & (0x1 << 3))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_4VNNIW;

                        // CPUID.(EAX=07H, ECX=00H):EDX.AVX512_VP2INTERSECT[bit 8]
                        if (r_eax07h.EDX & (0x1 << 8))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_VP2INTERSECT;

                        // CPUID.(EAX=07H, ECX=00H):EDX.AVX512_FP16[bit 23]
                        if (r_eax07h.EDX & (0x1 << 23))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_FP16;

                        //
                        // Decode EAX flags (subleaf 1)
                        //

                        // CPUID.(EAX=07H, ECX=01H):EAX.AVX512_BF16[bit 5]
                        if (r_eax07h_ecx01h.EAX & (0x1 << 5))
                            m_FeatureFlags |= (uint64_t)FF::AVX512_BF16;
                    }
                }
            }
        }
    }
}

void CpuidInfo::LoadInfo5(void)
{
    if (m_MaxEax < 4)
        return;

    bool done = false;
    uint32_t index = 0;

    while (!done)
    {
        CpuidRegs r;

        Cpuid__(4, index, &r);

        uint32_t cache_type = r.EAX & 0x1f;
        uint32_t cache_level = ((r.EAX >> 5) & 0x3);

        if (cache_type == 0)
            done = true;
        else
        {
            uint32_t ways = ((r.EBX >> 22) & 0x3ff) + 1;
            uint32_t partitions = ((r.EBX >> 12) & 0x3ff) + 1;
            uint32_t line_size = (r.EBX & 0xfff) + 1;
            uint32_t sets = r.ECX + 1;
            uint32_t cache_size = ways * partitions * line_size * sets;

            CacheInfo ci(cache_level, cache_type, cache_size);
            m_CacheInfo.push_back(ci);
            index++;
        }
    }
}

void CpuidInfo::Init(void)
{
    m_MaxEax = 0;
    m_MaxEaxExt = 0;
    m_FeatureFlags = 0;
    m_OsXsave = false;
    m_OsAvxState = false;
    m_OsAvx512State = false;
    m_VendorId[0] = '\0';
    m_ProcessorBrand[0] = '\0';
    m_CacheInfo.clear();
}

void CpuidInfo::InitProcessorBrand(void)
{
    if (m_MaxEaxExt >= 0x80000004)
    {
        CpuidRegs r2, r3, r4;
        uint32_t* p = (uint32_t*)m_ProcessorBrand;

        Cpuid__(0x80000002, 0, &r2);
        Cpuid__(0x80000003, 0, &r3);
        Cpuid__(0x80000004, 0, &r4);

        p[0] = r2.EAX;
        p[1] = r2.EBX;
        p[2] = r2.ECX;
        p[3] = r2.EDX;
        p[4] = r3.EAX;
        p[5] = r3.EBX;
        p[6] = r3.ECX;
        p[7] = r3.EDX;
        p[8] = r4.EAX;
        p[9] = r4.EBX;
        p[10] = r4.ECX;
        p[11]= r4.EDX;

        m_ProcessorBrand[sizeof(m_ProcessorBrand) - 1] = '\0';
    }
    else
    {
#if defined(_MSC_VER)
        strcpy_s(m_ProcessorBrand, "Unknown");
#else
        strcpy(m_ProcessorBrand, "Unknown");
#endif
    }
}
