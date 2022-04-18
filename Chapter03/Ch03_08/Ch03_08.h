//------------------------------------------------
//               Ch03_08.h
//------------------------------------------------

#pragma once
#include <vector>
#include "MatrixF32.h"

// Ch03_08_fcpp.cpp
extern std::vector<float> CalcColumnMeansF32_Cpp(const MatrixF32& x);
extern std::vector<float> CalcColumnMeansF32_Iavx(const MatrixF32& x);

// Miscellaneous constants
const unsigned int c_RngSeed = 41;
const float c_MatrixFillMin = 1.0f;
const float c_MatrixFillMax = 80.0f;

