//------------------------------------------------
//               Ch18_04.h
//------------------------------------------------

#pragma once
#include "MatrixF32.h"

// Ch18_04_fcpp.cpp
void MatrixMulF32_Cpp(MatrixF32& c, const MatrixF32& a, const MatrixF32& b);

// Ch18_04_fasm.asm
extern "C" void MatrixMulF32_Aavx512(float* c, const float* a, const float* b,
    const size_t* sizes);

// Ch18_04_misc.cpp
bool CheckArgs(const MatrixF32& c, const MatrixF32& a, const MatrixF32& b);
void InitMat(MatrixF32& c1, MatrixF32& c2, MatrixF32& a, MatrixF32& b);
void SaveResults(const MatrixF32& c1, const MatrixF32& c2, const MatrixF32& a,
    const MatrixF32& b);

// Ch18_04_bm.cpp
void MatrixMulF32_bm(void);
