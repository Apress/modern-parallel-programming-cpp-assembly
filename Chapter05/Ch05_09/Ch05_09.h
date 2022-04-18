//------------------------------------------------
//               Ch05_09.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include "MatrixF64.h"

// Ch05_09_fcpp.cpp
bool MatrixInvF64_Cpp(MatrixF64& a_inv, const MatrixF64& a, double epsilon);
bool MatrixInvF64_Iavx2(MatrixF64& a_inv, const MatrixF64& a, double epsilon);

// Ch05_09_fcpp2.cpp
MatrixF64 MatrixAddF64_Iavx2(const MatrixF64& a, const MatrixF64& b);
MatrixF64 MatrixMulF64_Iavx2(const MatrixF64& a, const MatrixF64& b);
void MatrixMulScalarF64_Iavx2(MatrixF64& c, const MatrixF64& a, double s_val);

// Ch05_09_misc.cpp
MatrixF64 GetTestMatrix(size_t id, double* epsilon);
size_t GetNumTestMatrices(void);

// Ch05_09_bm.cpp
void CalcMatrixInvF64_bm(void);

// Miscellaenous constants
const double c_DefaultEpsilon = 1.0e-5;
