//------------------------------------------------
//               Ch05_07.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include "MatrixF64.h"

struct Vec4x1_F64
{
    double W, X, Y, Z;
};

// Ch05_07_fcpp.cpp
extern void MatVecMulF64_Cpp(Vec4x1_F64* vec_b, MatrixF64& m,
    Vec4x1_F64* vec_a, size_t num_vec);
extern void MatVecMulF64_Iavx2(Vec4x1_F64* vec_b, MatrixF64& m,
    Vec4x1_F64* vec_a, size_t num_vec);

// Ch05_07_misc.cpp
extern bool CheckArgs(const Vec4x1_F64* vec_b, const MatrixF64& m,
    const Vec4x1_F64* vec_a, size_t num_vec);
extern void Init(MatrixF64& m, Vec4x1_F64* va, size_t num_vec);
extern bool VecCompare(const Vec4x1_F64* v1, const Vec4x1_F64* v2);

// Ch05_07_bm.cpp
extern void MatrixVecMulF64_bm(void);

// Miscellaenous constants
const size_t c_Alignment = 32;
const int c_RngMinVal = 1;
const int c_RngMaxVal = 500;
const unsigned int c_RngSeedVal = 187;
