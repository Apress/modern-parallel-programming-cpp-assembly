//------------------------------------------------
//               Ch14_01.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ch14_01.h"

static void PackedMathF32();
static void PackedMathF64();

static const char* c_OprStr[8] =
{
    "Add", "Sub", "Mul", "Div", "Min", "Max", "Sqrt a", "Abs b" 
};

int main()
{
    const char nl = '\n';

    PackedMathF32();
    std::cout << nl << std::string(78, '-') << nl;
    PackedMathF64();
}

static void PackedMathF32(void)
{
    YmmVal a, b, c[8];
    const char nl = '\n';

    a.m_F32[0] = 36.0f;                 b.m_F32[0] = -(float)(1.0 / 9.0);
    a.m_F32[1] = (float)(1.0 / 32.0);   b.m_F32[1] = 64.0f;
    a.m_F32[2] = 2.0f;                  b.m_F32[2] = -0.0625f;
    a.m_F32[3] = 42.0f;                 b.m_F32[3] = 8.666667f;
    a.m_F32[4] = (float)M_PI;           b.m_F32[4] = -4.0;
    a.m_F32[5] = 18.6f;                 b.m_F32[5] = -64.0f;
    a.m_F32[6] = 3.0f;                  b.m_F32[6] = -5.95f;
    a.m_F32[7] = 142.0f;                b.m_F32[7] = (float)M_SQRT2;

    PackedMathF32_Aavx(c, &a, &b);

    size_t w = 9;
    std::cout << ("\nResults for PackedMathF32_Aavx\n");

    for (unsigned int i = 0; i < 2; i++)
    {
        std::string s0 = (i == 0) ? "a lo:    " : "a hi:    ";
        std::string s1 = (i == 0) ? "b lo:    " : "b hi:    ";

        std::cout << s0 << a.ToStringF32(i) << nl;
        std::cout << s1 << b.ToStringF32(i) << nl;

        for (unsigned int j = 0; j < 8; j++)
        {
            std::cout << std::setw(w) << std::left << c_OprStr[j];
            std::cout << c[j].ToStringF32(i) << nl;
        }

        if (i == 0)
            std::cout << nl;
    }
}

static void PackedMathF64(void)
{
    YmmVal a, b, c[8];
    const char nl = '\n';

    a.m_F64[0] = 2.0;           b.m_F64[0] = M_PI;
    a.m_F64[1] = 4.0 ;          b.m_F64[1] = M_E;
    a.m_F64[2] = 7.5;           b.m_F64[2] = -9.125;
    a.m_F64[3] = 3.0;           b.m_F64[3] = -M_PI;
   
    PackedMathF64_Aavx(c, &a, &b);

    size_t w = 9;
    std::cout << ("\nResults for PackedMathF64_Aavx\n");

    for (unsigned int i = 0; i < 2; i++)
    {
        std::string s0 = (i == 0) ? "a lo:    " : "a hi:    ";
        std::string s1 = (i == 0) ? "b lo:    " : "b hi:    ";

        std::cout << s0 << a.ToStringF64(i) << nl;
        std::cout << s1 << b.ToStringF64(i) << nl;

        for (unsigned int j = 0; j < 8; j++)
        {
            std::cout << std::setw(w) << std::left << c_OprStr[j];
            std::cout << c[j].ToStringF64(i) << nl;
        }

        if (i == 0)
            std::cout << nl;
    }
}
