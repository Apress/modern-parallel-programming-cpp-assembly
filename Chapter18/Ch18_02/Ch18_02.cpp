//------------------------------------------------
//               Ch08_02.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <limits>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ch18_02.h"

static void PackedCompareF32(void);
static void PackedCompareF64(void);
static const char* c_CmpStr[8] = { "EQ", "NE", "LT", "LE", "GT", "GE", "OD", "UO" };

int main()
{
    PackedCompareF32();
    PackedCompareF64();
    return 0;
}

static void PackedCompareF32(void)
{
    ZmmVal a, b;
    uint16_t c[8];
    const char nl = '\n';
    constexpr float qnan_f32 = std::numeric_limits<float>::quiet_NaN();

    a.m_F32[0] = 2.0f;                  b.m_F32[0] = 1.0f;
    a.m_F32[1] = 7.0f;                  b.m_F32[1] = 12.0f;
    a.m_F32[2] = -6.0f;                 b.m_F32[2] = -6.0f;
    a.m_F32[3] = 3.0f;                  b.m_F32[3] = 8.0f;
    a.m_F32[4] = -16.0f;                b.m_F32[4] = -36.0f;
    a.m_F32[5] = 3.5f;                  b.m_F32[5] = 3.5f;
    a.m_F32[6] = (float)M_PI;           b.m_F32[6] = -6.0f;
    a.m_F32[7] = (float)M_SQRT2;        b.m_F32[7] = qnan_f32;
    a.m_F32[8] = 102.0f;                b.m_F32[8] = (float)M_SQRT1_2;
    a.m_F32[9] = 77.0f;                 b.m_F32[9] = 77.0f;
    a.m_F32[10] = 187.0f;               b.m_F32[10] = 33.0f;
    a.m_F32[11] = -5.1f;                b.m_F32[11] = -87.0f;
    a.m_F32[12] = 16.0f;                b.m_F32[12] = 936.0f;
    a.m_F32[13] = 0.5f;                 b.m_F32[13] = 0.5f;
    a.m_F32[14] = (float)(M_PI * 2);    b.m_F32[14] = 66.6667f;
    a.m_F32[15] = (float)(1.0/M_SQRT2); b.m_F32[15] = 100.7f;

    PackedCompareF32_Aavx512(c, &a, &b);

    const size_t w1 = 10;
    const size_t w2 = 6;
    std::cout << ("\nResults for PackedCompareF32\n");
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "      a          b    ";

    for (unsigned int j = 0; j < 8; j++)
        std::cout << std::setw(w2) << c_CmpStr[j];
    std::cout << nl << std::string(70, '-') << nl;

    for (unsigned int i = 0; i < 16; i++)
    {
        std::cout << std::setw(w1) << a.m_F32[i] << " ";
        std::cout << std::setw(w1) << b.m_F32[i];

        for (unsigned int j = 0; j < 8; j++)
            std::cout << std::setw(w2) << ((c[j] & (1 << i)) ? 1 : 0);

        std::cout << nl;
    }
}

static void PackedCompareF64(void)
{
    ZmmVal a, b;
    uint8_t c[8];
    const char nl = '\n';
    constexpr double qnan_f64 = std::numeric_limits<double>::quiet_NaN();

    a.m_F64[0] = 2.0;           b.m_F64[0] = M_E;
    a.m_F64[1] = M_PI / 2.0;    b.m_F64[1] = -M_1_PI;
    a.m_F64[2] = 12.0;          b.m_F64[2] = 42.0;
    a.m_F64[3] = 33.33333;      b.m_F64[3] = M_SQRT2;
    a.m_F64[4] = 0.5;           b.m_F64[4] = M_E * 2.0;
    a.m_F64[5] = -M_PI;         b.m_F64[5] = -M_PI * 2.0;
    a.m_F64[6] = -24.0;         b.m_F64[6] = -24.0;
    a.m_F64[7] = qnan_f64;      b.m_F64[7] = 100.0;

    PackedCompareF64_Aavx512(c, &a, &b);

    const size_t w1 = 10;
    const size_t w2 = 6;
    std::cout << ("\nResults for PackedCompareF64\n");
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "      a          b    ";

    for (unsigned int j = 0; j < 8; j++)
        std::cout << std::setw(w2) << c_CmpStr[j];
    std::cout << nl << std::string(70, '-') << nl;

    for (unsigned int i = 0; i < 8; i++)
    {
        std::cout << std::setw(w1) << a.m_F64[i] << " ";
        std::cout << std::setw(w1) << b.m_F64[i];

        for (unsigned int j = 0; j < 8; j++)
            std::cout << std::setw(w2) << ((c[j] & (1 << i)) ? 1 : 0);

        std::cout << nl;
    }
}
