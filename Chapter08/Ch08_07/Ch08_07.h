//------------------------------------------------
//               Ch08_07.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include "MatrixF32.h"

struct Vec4x1_F32
{
    float W, X, Y, Z;
};

// Ch08_07_fcpp.cpp
extern void MatVecMulF32_Cpp(Vec4x1_F32* vec_b, MatrixF32& m,
    Vec4x1_F32* vec_a, size_t num_vec);
extern void MatVecMulF32a_Iavx512(Vec4x1_F32* vec_b, MatrixF32& m,
    Vec4x1_F32* vec_a, size_t num_vec);
extern void MatVecMulF32b_Iavx512(Vec4x1_F32* vec_b, MatrixF32& m,
    Vec4x1_F32* vec_a, size_t num_vec);

// Ch08_07_misc.cpp
extern bool CheckArgs(const Vec4x1_F32* vec_b, const MatrixF32& m,
    const Vec4x1_F32* vec_a, size_t num_vec);
extern void Init(MatrixF32& m, Vec4x1_F32* va, size_t num_vec);
extern bool VecCompare(const Vec4x1_F32* v1, const Vec4x1_F32* v2);

// Ch08_07_bm.cpp
extern void MatrixVecMulF32_bm(void);

// Miscellaenous constants
const size_t c_Alignment = 64;
const int c_RngMinVal = 1;
const int c_RngMaxVal = 500;
const unsigned int c_RngSeedVal = 187;
