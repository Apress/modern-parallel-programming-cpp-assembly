//------------------------------------------------
//               Ch05_04.h
//------------------------------------------------

#pragma once
#include "MatrixF32.h"

// Ch05_04_fcpp.cpp
extern void MatrixMul4x4F32_Cpp(MatrixF32& c, const MatrixF32& a,
    const MatrixF32& b);
extern void MatrixMul4x4F32_Iavx2(MatrixF32& c, const MatrixF32& a,
    const MatrixF32& b);

// Ch05_04_misc.cpp
extern void InitMat(MatrixF32& c1, MatrixF32& c2, MatrixF32& a, MatrixF32& b);

// Ch05_04_bm.cpp
extern void MatrixMul4x4F32_bm(void);
