//------------------------------------------------
//               Ch08_06.h
//------------------------------------------------

#pragma once
#include "MatrixF64.h"

// Ch08_06_fcpp.cpp
void MatrixMulF64_Cpp(MatrixF64& c, const MatrixF64& a, const MatrixF64& b);
void MatrixMulF64_Iavx512(MatrixF64& c, const MatrixF64& a, const MatrixF64& b);

// Ch08_06_misc.cpp
bool CheckArgs(const MatrixF64& c, const MatrixF64& a, const MatrixF64& b);
void InitMat(MatrixF64& c1, MatrixF64& c2, MatrixF64& a, MatrixF64& b);
void SaveResults(const MatrixF64& c1, const MatrixF64& c2, const MatrixF64& a, const MatrixF64& b);

// Ch08_06_bm.cpp
void MatrixMulF64_bm(void);
