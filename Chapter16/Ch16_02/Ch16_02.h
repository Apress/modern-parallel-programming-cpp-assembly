//------------------------------------------------
//               Ch16_02.h
//------------------------------------------------

#pragma once
#include "MatrixF32.h"

// Ch16_02_fcpp.cpp
extern void MatrixMulF32_Cpp(MatrixF32& c, const MatrixF32& a, const MatrixF32& b);

// Ch16_02_fasm2.asm
extern "C" void MatrixMulF32_Aavx2(float* c, const float* a, const float* b,
    const size_t* sizes);

// Ch16_02_misc.cpp
extern bool CheckArgs(const MatrixF32& c, const MatrixF32& a, const MatrixF32& b);
extern void InitMat(MatrixF32& c1, MatrixF32& c2, MatrixF32& a, MatrixF32& b);
extern void SaveResults(const MatrixF32& c1, const MatrixF32& c2, const MatrixF32& a,
    const MatrixF32& b);

// Ch16_02_bm.cpp
extern void MatrixMulF32_bm(void);

// Ch16_02_test.cpp
extern void MatrixMulF32p_Iavx2(MatrixF32& c, const MatrixF32& a, const MatrixF32& b);
