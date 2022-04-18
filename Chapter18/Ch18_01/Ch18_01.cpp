//------------------------------------------------
//               Ch08_01.cpp
//------------------------------------------------

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ch18_01.h"

static void PackedMathF32(void);
static void PackedMathF64(void);

int main()
{
    PackedMathF32();
    PackedMathF64();
}

static void PackedMathF32(void)
{
    ZmmVal a, b, c[9];
    const char nl = '\n';

    a.m_F32[0] = 36.333333f;            b.m_F32[0] = -0.1111111f;
    a.m_F32[1] = 0.03125f;              b.m_F32[1] = 64.0f;
    a.m_F32[2] = 2.0f;                  b.m_F32[2] = -0.0625f;
    a.m_F32[3] = 42.0f;                 b.m_F32[3] = 8.666667f;
    a.m_F32[4] = 7.0f;                  b.m_F32[4] = -18.125f;
    a.m_F32[5] = 20.5f;                 b.m_F32[5] = 56.0f;
    a.m_F32[6] = 36.125f;               b.m_F32[6] = 24.0f;
    a.m_F32[7] = 0.5f;                  b.m_F32[7] = -158.444444f;

    a.m_F32[8] = 136.77777f;            b.m_F32[8] = -9.1111111f;
    a.m_F32[9] = 2.03125f;              b.m_F32[9] = 864.0f;
    a.m_F32[10] = 32.0f;                b.m_F32[10] = -70.0625f;
    a.m_F32[11] = 442.0f;               b.m_F32[11] = 98.666667f;
    a.m_F32[12] = 57.0f;                b.m_F32[12] = -518.125f;
    a.m_F32[13] = 620.5f;               b.m_F32[13] = 456.0f;
    a.m_F32[14] = 736.125f;             b.m_F32[14] = (float)M_PI;
    a.m_F32[15] = (float)M_E;           b.m_F32[15] = -298.6f;

    PackedMathF32_Aavx512(c, &a, &b);

    std::cout << ("\nResults for PackedMathF32\n");

    for (unsigned int i = 0; i < 4; i++)
    {
        std::cout << "Group #" << i << nl;
        std::cout << "  a:              " << a.ToStringF32(i) << nl;
        std::cout << "  b:              " << b.ToStringF32(i) << nl;
        std::cout << "  addps:          " << c[0].ToStringF32(i) << nl;
        std::cout << "  addps {rd-sae}: " << c[1].ToStringF32(i) << nl;
        std::cout << "  subps:          " << c[2].ToStringF32(i) << nl;
        std::cout << "  mulps:          " << c[3].ToStringF32(i) << nl;
        std::cout << "  divps:          " << c[4].ToStringF32(i) << nl;
        std::cout << "  minps:          " << c[5].ToStringF32(i) << nl;
        std::cout << "  maxps:          " << c[6].ToStringF32(i) << nl;
        std::cout << "  sqrtps:         " << c[7].ToStringF32(i) << nl;
        std::cout << "  absps:          " << c[8].ToStringF32(i) << nl;
        std::cout << nl;
    }
}

static void PackedMathF64(void)
{
    ZmmVal a, b, c[9];
    const char nl = '\n';

    a.m_F64[0] = M_E;                 b.m_F64[0] = M_PI;
    a.m_F64[1] = M_LOG10E;            b.m_F64[1] = M_E;
    a.m_F64[2] = M_SQRT2 / 5;         b.m_F64[2] = M_LN2;
    a.m_F64[3] = 7.0;                 b.m_F64[3] = -M_PI;

    a.m_F64[4] = M_LN10;              b.m_F64[4] = M_PI / 3;
    a.m_F64[5] = M_1_PI;              b.m_F64[5] = M_E;
    a.m_F64[6] = M_2_SQRTPI;          b.m_F64[6] = M_PI;
    a.m_F64[7] = M_SQRT2;             b.m_F64[7] = -M_PI / 2;
   
    PackedMathF64_Aavx512(c, &a, &b);
    std::cout << ("\nResults for PackedMathF64\n");

    const int w = 32;
    const int p = 16;

    for (unsigned int i = 0; i < 4; i++)
    {
        std::cout << "Group #" << i << nl;

        std::cout << "  a:              " << a.ToStringF64(i, w, p) << nl;
        std::cout << "  b:              " << b.ToStringF64(i, w, p) << nl;
        std::cout << "  addpd:          " << c[0].ToStringF64(i, w, p) << nl;
        std::cout << "  subpd:          " << c[1].ToStringF64(i, w, p) << nl;
        std::cout << "  mulpd:          " << c[2].ToStringF64(i, w, p) << nl;
        std::cout << "  divpd:          " << c[3].ToStringF64(i, w, p) << nl;
        std::cout << "  divpd {ru-sae}: " << c[4].ToStringF64(i, w, p) << nl;
        std::cout << "  minpd:          " << c[5].ToStringF64(i, w, p) << nl;
        std::cout << "  maxpd:          " << c[6].ToStringF64(i, w, p) << nl;
        std::cout << "  sqrtpd:         " << c[7].ToStringF64(i, w, p) << nl;
        std::cout << "  abspd:          " << c[8].ToStringF64(i, w, p) << nl;
        std::cout << nl;
    }
}
