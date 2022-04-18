//------------------------------------------------
//               Ch05_05.h
//------------------------------------------------

#pragma once
#include "MatrixF64.h"

// Ch05_05_fcpp.cpp
extern void MatrixMul4x4F64_Cpp(MatrixF64& c, const MatrixF64& a,
    const MatrixF64& b);
extern void MatrixMul4x4F64_Iavx2(MatrixF64& c, const MatrixF64& a,
    const MatrixF64& b);

// Ch05_05_misc.cpp
extern void InitMat(MatrixF64& c1, MatrixF64& c2, MatrixF64& a, MatrixF64& b);

// Ch05_05_bm.cpp
extern void MatrixMul4x4F64_bm(void);
