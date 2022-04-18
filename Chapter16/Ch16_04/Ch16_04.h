//------------------------------------------------
//               Ch16_04.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include "MatrixF32.h"

// Simple 4x1 vector structure
struct Vec4x1_F32
{
    float W, X, Y, Z;
};

// Ch16_04_fcpp.cpp
extern void MatVecMulF32_Cpp(Vec4x1_F32* vec_b, const MatrixF32& m, const Vec4x1_F32* vec_a, size_t num_vec);

// Ch16_04_fasm.asm
extern "C" void MatVecMulF32_Aavx2(Vec4x1_F32* vec_b, const float* m, const Vec4x1_F32* vec_a, size_t num_vec);

// Ch16_04_misc.cpp
extern "C" bool CheckArgs(const Vec4x1_F32* vec_b, const MatrixF32& m, const Vec4x1_F32* vec_a, size_t num_vec);
extern void Init(MatrixF32& m, Vec4x1_F32* va, size_t num_vec);
extern bool VecCompare(const Vec4x1_F32* v1, const Vec4x1_F32* v2);

// Ch16_04_bm.cpp
extern void MatrixVecMulF32_bm(void);

// Miscellaenous constants
const size_t c_Alignment = 32;
const int c_RngMinVal = 1;
const int c_RngMaxVal = 500;
const unsigned int c_RngSeedVal = 187;

