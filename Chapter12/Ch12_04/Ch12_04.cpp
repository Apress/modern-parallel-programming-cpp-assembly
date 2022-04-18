//------------------------------------------------
//               Ch12_04.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <string>
#include <limits>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ch12_04.h"

const std::string c_RcStrings[] = {"Nearest", "Down", "Up", "Zero"};
const RC c_RcVals[] = {RC::Nearest, RC::Down, RC::Up, RC::Zero};
const size_t c_NumRC = sizeof(c_RcVals) / sizeof (RC);

static void ConvertScalars(void);

int main()
{
    ConvertScalars();
    return 0;
}

static void ConvertScalars(void)
{
    const char nl = '\n';
    Uval src1, src2, src3, src4, src5, src6, src7;

    src1.m_F32 = (float)M_PI;
    src2.m_F32 = (float)-M_E;
    src3.m_F64 = M_SQRT2;
    src4.m_F64 = M_SQRT1_2;
    src5.m_F64 = 1.0 + DBL_EPSILON;
    src6.m_I32 = std::numeric_limits<int>::max();
    src7.m_I64 = std::numeric_limits<long long>::max();

std::cout << "----- Results for ConvertScalars() -----\n";

    for (size_t i = 0; i < c_NumRC; i++)
    {
        RC rc = c_RcVals[i];
        Uval des1, des2, des3, des4, des5, des6, des7;

        ConvertScalar_Aavx(&des1, &src1, CvtOp::F32_I32, rc);
        ConvertScalar_Aavx(&des2, &src2, CvtOp::F32_I64, rc);
        ConvertScalar_Aavx(&des3, &src3, CvtOp::F64_I32, rc);
        ConvertScalar_Aavx(&des4, &src4, CvtOp::F64_I64, rc);
        ConvertScalar_Aavx(&des5, &src5, CvtOp::F64_F32, rc);
        ConvertScalar_Aavx(&des6, &src6, CvtOp::I32_F32, rc);
        ConvertScalar_Aavx(&des7, &src7, CvtOp::I64_F64, rc);

        std::cout << std::fixed;
        std::cout << "\nRounding control = " << c_RcStrings[(int)rc] << nl;

        std::cout << "  F32_I32: " << std::setprecision(8);
        std::cout << src1.m_F32 << " --> " << des1.m_I32 << nl;

        std::cout << "  F32_I64: " << std::setprecision(8);
        std::cout << src2.m_F32 << " --> " << des2.m_I64 << nl;

        std::cout << "  F64_I32: " << std::setprecision(8);
        std::cout << src3.m_F64 << " --> " << des3.m_I32 << nl;

        std::cout << "  F64_I64: " << std::setprecision(8);
        std::cout << src4.m_F64 << " --> " << des4.m_I64 << nl;

        std::cout << "  F64_F32: ";
        std::cout << std::setprecision(16) << src5.m_F64 << " --> ";
        std::cout << std::setprecision(8) << des5.m_F32 << nl;

        std::cout << "  I32_F32: " << std::setprecision(8);
        std::cout << src6.m_I32 << " --> " << des6.m_F32 << nl;

        std::cout << "  I64_F64: " << std::setprecision(8);
        std::cout << src7.m_I64 << " --> " << des7.m_F64 << nl;
    }
}
