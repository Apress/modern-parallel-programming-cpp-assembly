//------------------------------------------------
//               Ch13_04.cpp
//------------------------------------------------

#include <iostream>
#include "Ch13_04.h"

static void ShiftU16(void);

int main()
{
    ShiftU16();
    return 0;
}

static void ShiftU16(void)
{
    XmmVal a, c;
    const int count_l = 8;
    const int count_r = 4;
    const char nl = '\n';

    a.m_U16[0] = 0x1234;
    a.m_U16[1] = 0xFFB0;
    a.m_U16[2] = 0x00CC;
    a.m_U16[3] = 0x8080;
    a.m_U16[4] = 0x00FF;
    a.m_U16[5] = 0xAAAA;
    a.m_U16[6] = 0x0F0F;
    a.m_U16[7] = 0x0101;

    SllU16_Aavx(&c, &a, count_l);
    std::cout << "\nResults for SllU16_Aavx - count = " << count_l << nl;
    std::cout << "a: " << a.ToStringX16() << nl;
    std::cout << "c: " << c.ToStringX16() << nl;

    SrlU16_Aavx(&c, &a, count_r);
    std::cout << "\nResults for SrlU16_Aavx - count = " << count_r << nl;
    std::cout << "a: " << a.ToStringX16() << nl;
    std::cout << "c: " << c.ToStringX16() << nl;

    SraU16_Aavx(&c, &a, count_r);
    std::cout << "\nResults for SraU16_Aavx - count = " << count_r << nl;
    std::cout << "a: " << a.ToStringX16() << nl;
    std::cout << "c: " << c.ToStringX16() << nl;
}
