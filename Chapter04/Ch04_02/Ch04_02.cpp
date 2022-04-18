//------------------------------------------------
//               Ch04_02.cpp
//------------------------------------------------

#include <iostream>
#include <string>
#include "Ch04_02.h"

static void UnpackU32_U64(void);
static void PackI32_I16(void);

static const std::string c_Line(82, '-');

int main()
{
    UnpackU32_U64();
    PackI32_I16();
    return 0;
}

static void UnpackU32_U64(void)
{
    YmmVal a, b, c[2];
    const char nl = '\n';

    a.m_U32[0] = 0x00000000;  b.m_U32[0] = 0x88888888;
    a.m_U32[1] = 0x11111111;  b.m_U32[1] = 0x99999999;
    a.m_U32[2] = 0x22222222;  b.m_U32[2] = 0xaaaaaaaa;
    a.m_U32[3] = 0x33333333;  b.m_U32[3] = 0xbbbbbbbb;

    a.m_U32[4] = 0x44444444;  b.m_U32[4] = 0xcccccccc;
    a.m_U32[5] = 0x55555555;  b.m_U32[5] = 0xdddddddd;
    a.m_U32[6] = 0x66666666;  b.m_U32[6] = 0xeeeeeeee;
    a.m_U32[7] = 0x77777777;  b.m_U32[7] = 0xffffffff;

    UnpackU32_U64_Iavx2(c, &a, &b);

    std::cout << "\nResults for UnpackU32_U64_Iavx2\n" << c_Line << nl;

    std::cout << "a lo         " << a.ToStringX32(0) << nl;
    std::cout << "b lo         " << b.ToStringX32(0) << nl << nl;
    std::cout << "a hi         " << a.ToStringX32(1) << nl;
    std::cout << "b hi         " << b.ToStringX32(1) << nl << nl;

    std::cout << "c[0] lo qword" << c[0].ToStringX64(0) << nl;
    std::cout << "c[0] hi qword" << c[0].ToStringX64(1) << nl << nl;
    std::cout << "c[1] lo qword" << c[1].ToStringX64(0) << nl;
    std::cout << "c[1] hi qword" << c[1].ToStringX64(1) << nl << nl;
}

static void PackI32_I16(void)
{
    YmmVal a, b, c;
    const char nl = '\n';

    a.m_I32[0] = 10;          b.m_I32[0] = 32768;
    a.m_I32[1] = -200000;     b.m_I32[1] = 6500;
    a.m_I32[2] = 300000;      b.m_I32[2] = 42000;
    a.m_I32[3] = -4000;       b.m_I32[3] = -68000;

    a.m_I32[4] = 9000;        b.m_I32[4] = 25000;
    a.m_I32[5] = 80000;       b.m_I32[5] = 500000;
    a.m_I32[6] = 200;         b.m_I32[6] = -7000;
    a.m_I32[7] = -32769;      b.m_I32[7] = 12500;

    PackI32_I16_Iavx2(&c, &a, &b);

    std::cout << "\nResults for PackI32_I16_Iavx2\n" << c_Line << nl;

    std::cout << "a lo " << a.ToStringI32(0) << nl;
    std::cout << "a hi " << a.ToStringI32(1) << nl << nl;

    std::cout << "b lo " << b.ToStringI32(0) << nl;
    std::cout << "b hi " << b.ToStringI32(1) << nl << nl;
    std::cout << "c lo " << c.ToStringI16(0) << nl;
    std::cout << "c hi " << c.ToStringI16(1) << nl << nl;
}
