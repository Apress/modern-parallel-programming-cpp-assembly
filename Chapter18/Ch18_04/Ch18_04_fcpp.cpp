//------------------------------------------------
//               Ch18_04_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include "Ch18_04.h"
#include "MF.h"

void MatrixMulF32_Cpp(MatrixF32& c, const MatrixF32& a, const MatrixF32& b)
{
    MatrixF32::Mul(c, a, b);
}
