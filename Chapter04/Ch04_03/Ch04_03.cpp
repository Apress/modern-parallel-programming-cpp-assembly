//------------------------------------------------
//               Ch04_03.cpp
//------------------------------------------------

#include <iostream>
#include <string>
#include <cstdint>
#include "Ch04_03.h"

static void ZeroExtU8_U16(void);
static void ZeroExtU8_U32(void);
static void SignExtI16_I32(void);
static void SignExtI16_I64(void);

static const std::string c_Line(80, '-');

int main()
{
    ZeroExtU8_U16();
    ZeroExtU8_U32();
    SignExtI16_I32();
    SignExtI16_I64();
}

static void ZeroExtU8_U16(void)
{
    YmmVal a, c[2];
    const char nl = '\n';

    for (size_t i = 0; i < 32; i++)
        a.m_U8[i] = (uint8_t)(i * 8);

    ZeroExtU8_U16_Iavx2(c, &a);

    std::cout << "\nResults for ZeroExtU8_U16_Iavx2\n" << c_Line << nl;

    std::cout << "a (0:15):   " << a.ToStringU8(0) << nl;
    std::cout << "a (16:31):  " << a.ToStringU8(1) << nl;
    std::cout << nl;
    std::cout << "c (0:7):    " << c[0].ToStringU16(0) << nl;
    std::cout << "c (8:15):   " << c[0].ToStringU16(1) << nl;
    std::cout << "c (16:23):  " << c[1].ToStringU16(0) << nl;
    std::cout << "c (24:31):  " << c[1].ToStringU16(1) << nl;
}

static void ZeroExtU8_U32(void)
{
    YmmVal a, c[4];
    const char nl = '\n';

    for (size_t i = 0; i < 32; i++)
        a.m_U8[i] = (uint8_t)(255 - i * 8);

    ZeroExtU8_U32_Iavx2(c, &a);

    std::cout << "\nResults for ZeroExtU8_U32_Iavx2\n" << c_Line << nl;

    std::cout << "a (0:15):   " << a.ToStringU8(0) << nl;
    std::cout << "a (16:31):  " << a.ToStringU8(1) << nl;
    std::cout << nl;
    std::cout << "c (0:3):    " << c[0].ToStringU32(0) << nl;
    std::cout << "c (4:7):    " << c[0].ToStringU32(1) << nl;
    std::cout << "c (8:11):   " << c[1].ToStringU32(0) << nl;
    std::cout << "c (12:15):  " << c[1].ToStringU32(1) << nl;
    std::cout << "c (16:19):  " << c[2].ToStringU32(0) << nl;
    std::cout << "c (20:23):  " << c[2].ToStringU32(1) << nl;
    std::cout << "c (24:27):  " << c[3].ToStringU32(0) << nl;
    std::cout << "c (28:31):  " << c[3].ToStringU32(1) << nl;
}

static void SignExtI16_I32(void)
{
    YmmVal a, c[2];
    const char nl = '\n';

    for (size_t i = 0; i < 16; i++)
        a.m_I16[i] = (int16_t)(-32768 + i * 4000);

    SignExtI16_I32_Iavx2(c, &a);

    std::cout << "\nResults for SignExtI16_I32_Iavx2\n" << c_Line << nl;

    std::cout << "a (0:7):    " << a.ToStringI16(0) << nl;
    std::cout << "a (8:15):   " << a.ToStringI16(1) << nl;
    std::cout << nl;
    std::cout << "c (0:3):    " << c[0].ToStringI32(0) << nl;
    std::cout << "c (4:7):    " << c[0].ToStringI32(1) << nl;
    std::cout << "c (8:11):   " << c[1].ToStringI32(0) << nl;
    std::cout << "c (12:15):  " << c[1].ToStringI32(1) << nl;
}

static void SignExtI16_I64(void)
{
    YmmVal a, c[4];
    const char nl = '\n';

    for (size_t i = 0; i < 16; i++)
        a.m_I16[i] = (int16_t)(32767 - i * 4000);

    SignExtI16_I64_Iavx2(c, &a);

    std::cout << "\nResults for SignExtI16_I64_Iavx2\n" << c_Line << nl;

    std::cout << "a (0:7):    " << a.ToStringI16(0) << nl;
    std::cout << "a (8:15):   " << a.ToStringI16(1) << nl;
    std::cout << nl;
    std::cout << "c (0:1):    " << c[0].ToStringI64(0) << nl;
    std::cout << "c (2:3):    " << c[0].ToStringI64(1) << nl;
    std::cout << "c (4:5):    " << c[1].ToStringI64(0) << nl;
    std::cout << "c (6:7):    " << c[1].ToStringI64(1) << nl;
    std::cout << "c (8:9):    " << c[2].ToStringI64(0) << nl;
    std::cout << "c (10:11):  " << c[2].ToStringI64(1) << nl;
    std::cout << "c (12:13):  " << c[3].ToStringI64(0) << nl;
    std::cout << "c (14:15):  " << c[3].ToStringI64(1) << nl;
}
