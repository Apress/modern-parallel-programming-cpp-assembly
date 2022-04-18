//------------------------------------------------
//               Ch13_01.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch13_01.h"

static void AddI16(void);
static void SubI16(void);

int main()
{
    AddI16();
    SubI16();
    return 0;
}

static void AddI16(void)
{
    const char nl = '\n';
    XmmVal a, b, c1, c2;

    // Packed int16_t addition
    a.m_I16[0] = 10;          b.m_I16[0] = 100;
    a.m_I16[1] = 200;         b.m_I16[1] = -200;
    a.m_I16[2] = 30;          b.m_I16[2] = 32760;
    a.m_I16[3] = -32766;      b.m_I16[3] = -400;
    a.m_I16[4] = 50;          b.m_I16[4] = 500;
    a.m_I16[5] = 60;          b.m_I16[5] = -600;
    a.m_I16[6] = 32000;       b.m_I16[6] = 1200;
    a.m_I16[7] = -32000;      b.m_I16[7] = -950;

    AddI16_Aavx(&c1, &c2, &a, &b);

    std::cout << "\nResults for AddI16_Aavx - Wraparound Addition\n";
    std::cout << "a:  " << a.ToStringI16() << nl;
    std::cout << "b:  " << b.ToStringI16() << nl;
    std::cout << "c1: " << c1.ToStringI16() << nl;
    std::cout << "\nResults for AddI16_Aavx - Saturated Addition\n";
    std::cout << "a:  " << a.ToStringI16() << nl;
    std::cout << "b:  " << b.ToStringI16() << nl;
    std::cout << "c2: " << c2.ToStringI16() << nl;

}

static void SubI16(void)
{
    const char nl = '\n';
    XmmVal a, b, c1, c2;

    a.m_I16[0] = 10;          b.m_I16[0] = 100;
    a.m_I16[1] = 200;         b.m_I16[1] = -200;
    a.m_I16[2] = -30;         b.m_I16[2] = 32760;
    a.m_I16[3] = -32766;      b.m_I16[3] = 400;
    a.m_I16[4] = 50;          b.m_I16[4] = 500;
    a.m_I16[5] = 60;          b.m_I16[5] = -600;
    a.m_I16[6] = 32000;       b.m_I16[6] = 1200;
    a.m_I16[7] = -32000;      b.m_I16[7] = 950;

    SubI16_Aavx(&c1, &c2, &a, &b);

    std::cout << "\nResults for SubI16_Aavx - Wraparound Subtraction\n";
    std::cout << "a:  " << a.ToStringI16() << nl;
    std::cout << "b:  " << b.ToStringI16() << nl;
    std::cout << "c1: " << c1.ToStringI16() << nl;
    std::cout << "\nResults for SubI16_Aavx - Saturated Subtraction\n";
    std::cout << "a:  " << a.ToStringI16() << nl;
    std::cout << "b:  " << b.ToStringI16() << nl;
    std::cout << "c2: " << c2.ToStringI16() << nl;
}
