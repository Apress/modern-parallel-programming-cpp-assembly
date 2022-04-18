//------------------------------------------------
//               Ch14_02.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>
#include "Ch14_02.h"

static void PackedCompareF32();
static void PackedCompareF64();

static const char* c_CmpStr[8] =
{
    "EQ", "NE", "LT", "LE", "GT", "GE", "ORDERED", "UNORDERED"
};

int main()
{
    const char nl = '\n';

    PackedCompareF32();
    std::cout << nl << std::string(80, '-') << nl;
    PackedCompareF64();
}

static void PackedCompareF32()
{
    YmmVal a, b, c[8];
    const char nl = '\n';
    constexpr float qnan_f32 = std::numeric_limits<float>::quiet_NaN();

    a.m_F32[0] = 2.0;               b.m_F32[0] = 1.0;
    a.m_F32[1] = 7.0;               b.m_F32[1] = 12.0;
    a.m_F32[2] = -6.0;              b.m_F32[2] = -6.0;
    a.m_F32[3] = 3.0;               b.m_F32[3] = 8.0;
    a.m_F32[4] = -16.0;             b.m_F32[4] = -36.0;
    a.m_F32[5] = 3.5;               b.m_F32[5] = 3.5;
    a.m_F32[6] = (float)M_PI;       b.m_F32[6] = -6.0;
    a.m_F32[7] = (float)M_SQRT2;    b.m_F32[7] = qnan_f32;

    PackedCompareF32_Aavx(c, &a, &b);

    size_t w = 9;
    std::cout << ("\nResults for PackedCompareF32_Aavx\n");

    for (unsigned int i = 0; i < 2; i++)
    {
        std::string s0 = (i == 0) ? "a lo:    " : "a hi:    ";
        std::string s1 = (i == 0) ? "b lo:    " : "b hi:    ";

        std::cout << s0 << a.ToStringF32(i) << nl;
        std::cout << s1 << b.ToStringF32(i) << nl;

        for (unsigned int j = 0; j < 8; j++)
        {
            std::cout << std::setw(w) << std::left << c_CmpStr[j];
            std::cout << c[j].ToStringX32(i) << nl;
        }

        if (i == 0)
            std::cout << nl;
    }
}

static void PackedCompareF64()
{
    YmmVal a, b, c[8];
    const char nl = '\n';
    constexpr double qnan_f64 = std::numeric_limits<double>::quiet_NaN();

    a.m_F64[0] = 2.0;       b.m_F64[0] = M_E;
    a.m_F64[1] = M_PI;      b.m_F64[1] = -M_1_PI;
    a.m_F64[2] = 12.0;      b.m_F64[2] = 42;
    a.m_F64[3] = qnan_f64;   b.m_F64[3] = M_SQRT2;

    PackedCompareF64_Aavx(c, &a, &b);

    size_t w = 9;
    std::cout << ("\nResults for PackedCompareF64_Aavx\n");

    for (unsigned int i = 0; i < 2; i++)
    {
        std::string s0 = (i == 0) ? "a lo:    " : "a hi:    ";
        std::string s1 = (i == 0) ? "b lo:    " : "b hi:    ";

        std::cout << s0 << a.ToStringF64(i) << nl;
        std::cout << s1 << b.ToStringF64(i) << nl;

        for (unsigned int j = 0; j < 8; j++)
        {
            std::cout << std::setw(w) << std::left << c_CmpStr[j];
            std::cout << c[j].ToStringX64(i) << nl;
        }

        if (i == 0)
            std::cout << nl;
    }
}
