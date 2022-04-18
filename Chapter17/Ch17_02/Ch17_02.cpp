//------------------------------------------------
//               Ch17_02.cpp
//------------------------------------------------


#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Ch17_02.h"

static void MaskOpI64a(void);
static void MaskOpI64b(void);
static void MaskOpI64c(void);

int main()
{
    MaskOpI64a();
    MaskOpI64b();
    MaskOpI64c();
    return 0;
}

static void MaskOpI64a(void)
{
    ZmmVal a, b, c[5];
    uint8_t mask = 0x7b;

    a.m_I64[0] = 64;        b.m_I64[0] = 4;
    a.m_I64[1] = 1024;      b.m_I64[1] = 5;
    a.m_I64[2] = -2048;     b.m_I64[2] = 2;
    a.m_I64[3] = 8192;      b.m_I64[3] = 5;
    a.m_I64[4] = -256;      b.m_I64[4] = 8;
    a.m_I64[5] = 4096;      b.m_I64[5] = 7;
    a.m_I64[6] = 16;        b.m_I64[6] = 3;
    a.m_I64[7] = 512;       b.m_I64[7] = 6;

    MaskOpI64a_Aavx512(c, mask, &a, &b);

    std::cout << "\nResults for MaskOpI64a ";
    std::cout << "(mask = 0x" << std::hex << (int)mask << std::dec << ")\n\n";
    std::cout << " i      a      b      add      sub      mul      sll      sra\n";
    std::cout << "-------------------------------------------------------------\n";

    for (size_t i = 0; i < 8; i++)
    {
        std::cout << std::setw(2) << i << ' ';
        std::cout << std::setw(6) << a.m_I64[i] << ' ';
        std::cout << std::setw(6) << b.m_I64[i] << ' ';
        std::cout << std::setw(8) << c[0].m_I64[i] << ' ';
        std::cout << std::setw(8) << c[1].m_I64[i] << ' ';
        std::cout << std::setw(8) << c[2].m_I64[i] << ' ';
        std::cout << std::setw(8) << c[3].m_I64[i] << ' ';
        std::cout << std::setw(8) << c[4].m_I64[i] << '\n';
    }
}

static void MaskOpI64b(void)
{
    ZmmVal a, b1, b2, c[5];
    uint8_t mask = 0xb6;

    a.m_I64[0] = 111111;   b1.m_I64[0] = 64;      b2.m_I64[0] = 4;
    a.m_I64[1] = 222222;   b1.m_I64[1] = 1024;    b2.m_I64[1] = 5;
    a.m_I64[2] = 333333;   b1.m_I64[2] = -2048;   b2.m_I64[2] = 2;
    a.m_I64[3] = 444444;   b1.m_I64[3] = 8192;    b2.m_I64[3] = 5;
    a.m_I64[4] = 555555;   b1.m_I64[4] = -256;    b2.m_I64[4] = 8;
    a.m_I64[5] = 666666;   b1.m_I64[5] = 4096;    b2.m_I64[5] = 7;
    a.m_I64[6] = 777777;   b1.m_I64[6] = 16;      b2.m_I64[6] = 3;
    a.m_I64[7] = 888888;   b1.m_I64[7] = 512;     b2.m_I64[7] = 6;

    MaskOpI64b_Aavx512(c, mask, &a, &b1, &b2);

    std::cout << "\nResults for MaskOpI64b ";
    std::cout << "(mask = 0x" << std::hex << (int)mask << std::dec << ")\n\n";
    std::cout << " i      a     b1     b2      add      sub      mul      sll      sra\n";
    std::cout << "--------------------------------------------------------------------\n";

    for (size_t i = 0; i < 8; i++)
    {
        std::cout << std::setw(2) << i << ' ';
        std::cout << std::setw(6) << a.m_I64[i] << ' ';
        std::cout << std::setw(6) << b1.m_I64[i] << ' ';
        std::cout << std::setw(6) << b2.m_I64[i] << ' ';
        std::cout << std::setw(8) << c[0].m_I64[i] << ' ';
        std::cout << std::setw(8) << c[1].m_I64[i] << ' ';
        std::cout << std::setw(8) << c[2].m_I64[i] << ' ';
        std::cout << std::setw(8) << c[3].m_I64[i] << ' ';
        std::cout << std::setw(8) << c[4].m_I64[i] << '\n';
    }
}

static void MaskOpI64c(void)
{
    ZmmVal a, c;
    int64_t x1 = 0;
    int64_t x2 = 42;

    a.m_I64[0] = -100;
    a.m_I64[1] = 200;
    a.m_I64[2] = 300;
    a.m_I64[3] = -400;
    a.m_I64[4] = -500;
    a.m_I64[5] = 600;
    a.m_I64[6] = 700;
    a.m_I64[7] = -800;

    MaskOpI64c_Aavx512(&c, &a, x1, x2);

    std::cout << "\nResults for MaskOpI64c";
    std::cout << " (x1 = " << x1 << ", x2 = " << x2 << ")\n\n";
    std::cout << " i        a        c\n";
    std::cout << "--------------------\n";

    for (size_t i = 0; i < 8; i++)
    {
        std::cout << std::setw(2)  << i << ' ';
        std::cout << std::setw(8) << a.m_I64[i] << ' ';
        std::cout << std::setw(8) << c.m_I64[i] << '\n';
    }
}
