//------------------------------------------------
//               Ch05_08.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include "MatrixF32.h"

// Ch05_08_fcpp.cpp
bool MatrixInvF32_Cpp(MatrixF32& a_inv, const MatrixF32& a, float epsilon);
bool MatrixInvF32_Iavx2(MatrixF32& a_inv, const MatrixF32& a, float epsilon);

// Ch05_08_fcpp2.cpp
MatrixF32 MatrixAddF32_Iavx2(const MatrixF32& a, const MatrixF32& b);
MatrixF32 MatrixMulF32_Iavx2(const MatrixF32& a, const MatrixF32& b);
void MatrixMulScalarF32_Iavx2(MatrixF32& c, const MatrixF32& a, float s_val);

// Ch05_08_misc.cpp
MatrixF32 GetTestMatrix(size_t id, float* epsilon);
size_t GetNumTestMatrices(void);

// Ch05_08_bm.cpp
void CalcMatrixInvF32_bm(void);

// Miscellaenous constants
const float c_DefaultEpsilon = 1.0e-5f;
