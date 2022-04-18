//------------------------------------------------
//               Ch18_05.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include "MatrixF32.h"

// Simple 4x1 vector structure
struct Vec4x1_F32
{
    float W, X, Y, Z;
};

// Ch18_05_fcpp.cpp
extern void MatVecMulF32_Cpp(Vec4x1_F32* vec_b, MatrixF32& m, Vec4x1_F32* vec_a, size_t num_vec);

// Ch18_04_fasm.asm
extern "C" void MatVecMulF32a_Aavx512(Vec4x1_F32* vec_b, const float* m, const Vec4x1_F32* vec_a, size_t num_vec);

// Ch18_04_fasm2.asm
extern "C" void MatVecMulF32b_Aavx512(Vec4x1_F32* vec_b, const float* m, const Vec4x1_F32* vec_a, size_t num_vec);

// Ch18_05_misc.cpp
extern bool CheckArgs(const Vec4x1_F32* vec_b, const MatrixF32& m, const Vec4x1_F32* vec_a, size_t num_vec);
extern void Init(MatrixF32& m, Vec4x1_F32* va, size_t num_vec);
extern bool VecCompare(const Vec4x1_F32* v1, const Vec4x1_F32* v2);

// Ch18_05_bm.cpp
extern void MatrixVecMulF32_bm(void);

// Miscellaenous constants
const size_t c_Alignment = 64;
const int c_RngMinVal = 1;
const int c_RngMaxVal = 500;
const unsigned int c_RngSeedVal = 187;
