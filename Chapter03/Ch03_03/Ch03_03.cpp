//------------------------------------------------
//               Ch03_03.cpp
//------------------------------------------------

#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ch03_03.h"

static void  PackedConvertF32(void);
static void  PackedConvertF64(void);

int main()
{
    std::string sep(80, '-');

    PackedConvertF32();
    std::cout << '\n' << sep << '\n';
    PackedConvertF64();
}

static void  PackedConvertF32(void)
{
    XmmVal a, c;

    a.m_I32[0] = 10;
    a.m_I32[1] = -500;
    a.m_I32[2] = 600;
    a.m_I32[3] = -1024;
    PackedConvertFP_Iavx(&c, &a, CvtOp::I32_TO_F32);
    std::cout << "\nResults for CvtOp::I32_TO_F32\n";
    std::cout << "a: " << a.ToStringI32() << '\n';
    std::cout << "c: " << c.ToStringF32() << '\n';

    a.m_F32[0] = 1.0f / 3.0f;
    a.m_F32[1] = 2.0f / 3.0f;
    a.m_F32[2] = -a.m_F32[0] * 2.0f;
    a.m_F32[3] = -a.m_F32[1] * 2.0f;
    PackedConvertFP_Iavx(&c, &a, CvtOp::F32_TO_I32);
    std::cout << "\nResults for CvtOp::F32_TO_I32\n";
    std::cout << "a: " << a.ToStringF32() << '\n';
    std::cout << "c: " << c.ToStringI32() << '\n';

    // F32_TO_F64 converts the two low-order F32 values of 'a'
    a.m_F32[0] = 1.0f / 7.0f;
    a.m_F32[1] = 2.0f / 9.0f;
    a.m_F32[2] = 0;
    a.m_F32[3] = 0;
    PackedConvertFP_Iavx(&c, &a, CvtOp::F32_TO_F64);
    std::cout << "\nResults for CvtOp::F32_TO_F64\n";
    std::cout << "a: " << a.ToStringF32() << '\n';
    std::cout << "c: " << c.ToStringF64() << '\n';
}

static void  PackedConvertF64(void)
{
    XmmVal a, c;

    // I32_TO_F64 converts the two low-order doubleword integers of 'a'
    a.m_I32[0] = 10;
    a.m_I32[1] = -20;
    a.m_I32[2] = 0;
    a.m_I32[3] = 0;
    PackedConvertFP_Iavx(&c, &a, CvtOp::I32_TO_F64);
    std::cout << "\nResults for CvtOp::I32_TO_F64\n";
    std::cout << "a: " << a.ToStringI32() << '\n';
    std::cout << "c: " << c.ToStringF64() << '\n';

    // F64_TO_I32 sets the two high-order doublewords of 'b' to zero
    a.m_F64[0] = M_PI;
    a.m_F64[1] = M_E;
    PackedConvertFP_Iavx(&c, &a, CvtOp::F64_TO_I32);
    std::cout << "\nResults for CvtOp::F64_TO_I32\n";
    std::cout << "a: " << a.ToStringF64() << '\n';
    std::cout << "c: " << c.ToStringI32() << '\n';

    // F64_TO_F32 sets the two high-order F32 values of 'b' to zero
    a.m_F64[0] = M_SQRT2;
    a.m_F64[1] = M_SQRT1_2;
    PackedConvertFP_Iavx(&c, &a, CvtOp::F64_TO_F32);
    std::cout << "\nResults for CvtOp::F64_TO_F32\n";
    std::cout << "a: " << a.ToStringF64() << '\n';
    std::cout << "c: " << c.ToStringF32() << '\n';
}
