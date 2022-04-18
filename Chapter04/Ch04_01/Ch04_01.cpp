//------------------------------------------------
//               Ch04_01.cpp
//------------------------------------------------

#include <iostream>
#include <string>
#include "Ch04_01.h"

static void MathI16(void);
static void MathI32(void);
static const std::string c_Line(75, '-');

int main()
{
    MathI16();
    MathI32();
    return 0;
}

static void MathI16(void)
{
    YmmVal a, b, c[6];
    const size_t w = 8;
    const char nl = '\n', sp = ' ';

    a.m_I16[0] = 10;       b.m_I16[0] = 1000;
    a.m_I16[1] = 20;       b.m_I16[1] = 2000;
    a.m_I16[2] = 3000;     b.m_I16[2] = 30;
    a.m_I16[3] = 4000;     b.m_I16[3] = 40;

    a.m_I16[4] = 30000;    b.m_I16[4] = 3000;       // add overflow
    a.m_I16[5] = 6000;     b.m_I16[5] = 32000;      // add overflow
    a.m_I16[6] = 2000;     b.m_I16[6] = -31000;     // sub overflow
    a.m_I16[7] = 4000;     b.m_I16[7] = -30000;     // sub overflow

    a.m_I16[8] = 4000;     b.m_I16[8] = -2500;
    a.m_I16[9] = 3600;     b.m_I16[9] = -1200;
    a.m_I16[10] = 6000;    b.m_I16[10] = 9000;
    a.m_I16[11] = -20000;  b.m_I16[11] = -20000;

    a.m_I16[12] = -25000;  b.m_I16[12] = -27000;    // add overflow
    a.m_I16[13] = 8000;    b.m_I16[13] = 28700;     // add overflow
    a.m_I16[14] = 3;       b.m_I16[14] = -32766;    // sub overflow
    a.m_I16[15] = -15000;  b.m_I16[15] = 24000;     // sub overflow

    MathI16_Iavx2(c, &a, &b);

    std::cout <<"\nResults for MathI16_Iavx2\n\n";
    std::cout << " i        a        b      add     adds";
    std::cout << "      sub     subs      min      max\n";
    std::cout << c_Line << nl;

    for (size_t i = 0; i < 16; i++)
    {
        std::cout << std::setw(2)  << i << sp;
        std::cout << std::setw(w) << a.m_I16[i] << sp;
        std::cout << std::setw(w) << b.m_I16[i] << sp;
        std::cout << std::setw(w) << c[0].m_I16[i] << sp;
        std::cout << std::setw(w) << c[1].m_I16[i] << sp;
        std::cout << std::setw(w) << c[2].m_I16[i] << sp;
        std::cout << std::setw(w) << c[3].m_I16[i] << sp;
        std::cout << std::setw(w) << c[4].m_I16[i] << sp;
        std::cout << std::setw(w) << c[5].m_I16[i] << nl;
    }
}

static void MathI32(void)
{
    YmmVal a, b, c[6];
    const size_t w = 8;
    const char nl = '\n', sp = ' ';

    a.m_I32[0] = 64;        b.m_I32[0] = 4;
    a.m_I32[1] = 1024;      b.m_I32[1] = 5;
    a.m_I32[2] = -2048;     b.m_I32[2] = 2;
    a.m_I32[3] = 8192;      b.m_I32[3] = 5;
    a.m_I32[4] = -256;      b.m_I32[4] = 8;
    a.m_I32[5] = 12288;     b.m_I32[5] = 7;
    a.m_I32[6] = 16;        b.m_I32[6] = 3;
    a.m_I32[7] = -512;      b.m_I32[7] = 6;

    MathI32_Iavx2(c, &a, &b);

    std::cout << "\nResults for MathI32_Iavx2\n\n";
    std::cout << " i        a        b      add      sub";
    std::cout << "     mull      sll      sra      abs\n";
    std::cout << c_Line << nl;

    for (size_t i = 0; i < 8; i++)
    {
        std::cout << std::setw(2) << i << sp;
        std::cout << std::setw(w) << a.m_I32[i] << sp;
        std::cout << std::setw(w) << b.m_I32[i] << sp;
        std::cout << std::setw(w) << c[0].m_I32[i] << sp;
        std::cout << std::setw(w) << c[1].m_I32[i] << sp;
        std::cout << std::setw(w) << c[2].m_I32[i] << sp;
        std::cout << std::setw(w) << c[3].m_I32[i] << sp;
        std::cout << std::setw(w) << c[4].m_I32[i] << sp;
        std::cout << std::setw(w) << c[5].m_I32[i] << nl;
    }
}
