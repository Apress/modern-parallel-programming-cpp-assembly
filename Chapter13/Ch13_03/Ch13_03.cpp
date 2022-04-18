//------------------------------------------------
//               Ch13_04.cpp
//------------------------------------------------

#include <iostream>
#include "Ch13_03.h"

static void BitwiseLogical(void);

int main()
{
    BitwiseLogical();
    return 0;
}

static void BitwiseLogical(void)
{
    XmmVal a, b, c;
    const char nl = '\n';

    a.m_U16[0] = 0x1234;      b.m_U16[0] = 0xFF00;
    a.m_U16[1] = 0xABDC;      b.m_U16[1] = 0x00FF;
    a.m_U16[2] = 0xAA55;      b.m_U16[2] = 0xAAAA;
    a.m_U16[3] = 0x1111;      b.m_U16[3] = 0x5555;
    a.m_U16[4] = 0xFFFF;      b.m_U16[4] = 0x8000;
    a.m_U16[5] = 0x7F7F;      b.m_U16[5] = 0x7FFF;
    a.m_U16[6] = 0x9876;      b.m_U16[6] = 0xF0F0;
    a.m_U16[7] = 0x7F00;      b.m_U16[7] = 0x0880;

    AndU16_Aavx(&c, &a, &b);
    std::cout << "\nResults for AndU16_Aavx\n";
    std::cout << "a: " << a.ToStringX16() << nl;
    std::cout << "b: " << b.ToStringX16() << nl;
    std::cout << "c: " << c.ToStringX16() << nl;

    OrU16_Aavx(&c, &a, &b);
    std::cout << "\nResults for OrU16_Aavx\n";
    std::cout << "a: " << a.ToStringX16() << nl;
    std::cout << "b: " << b.ToStringX16() << nl;
    std::cout << "c: " << c.ToStringX16() << nl;

    XorU16_Aavx(&c, &a, &b);
    std::cout << "\nResults for XorU16_Aavx\n";
    std::cout << "a: " << a.ToStringX16() << nl;
    std::cout << "b: " << b.ToStringX16() << nl;
    std::cout << "c: " << c.ToStringX16() << nl;
}
