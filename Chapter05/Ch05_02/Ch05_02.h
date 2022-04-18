//------------------------------------------------
//               Ch05_02.h
//------------------------------------------------

#pragma once
#include "MatrixF32.h"

// Ch05_02_fcpp.cpp
void MatrixMulF32_Cpp(MatrixF32& c, const MatrixF32& a, const MatrixF32& b);
void MatrixMulF32_Iavx2(MatrixF32& c, const MatrixF32& a, const MatrixF32& b);

// Ch05_02_misc.cpp
bool CheckArgs(const MatrixF32& c, const MatrixF32& a, const MatrixF32& b);
void InitMat(MatrixF32& c1, MatrixF32& c2, MatrixF32& a, MatrixF32& b);
void SaveResults(const MatrixF32& c1, const MatrixF32& c2, const MatrixF32& a,
    const MatrixF32& b);

// Ch05_02_bm.cpp
void MatrixMulF32_bm(void);
