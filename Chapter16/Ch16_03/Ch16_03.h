//------------------------------------------------
//               Ch16_03.h
//------------------------------------------------

#pragma once
#include "MatrixF32.h"

// Ch16_03_fcpp.cpp
extern void MatrixMul4x4F32_Cpp(MatrixF32& c, const MatrixF32& a, const MatrixF32& b);

// Ch16_03_fasm.asm
extern "C" void MatrixMul4x4F32a_Aavx2(float* c, const float* a, const float* b);
extern "C" void MatrixMul4x4F32b_Aavx2(float* c, const float* a, const float* b);

// Ch16_03_misc.cpp
extern void InitMat(MatrixF32& c1, MatrixF32& c2, MatrixF32& c3, MatrixF32& a, MatrixF32& b);

// Ch16_03_bm.cpp
extern void MatrixMul4x4F32_bm(void);
