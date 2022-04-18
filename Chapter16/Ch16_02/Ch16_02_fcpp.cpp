//------------------------------------------------
//               Ch16_02_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include "Ch16_02.h"

void MatrixMulF32_Cpp(MatrixF32& c, const MatrixF32& a, const MatrixF32& b)
{
    MatrixF32::Mul(c, a, b);
}
