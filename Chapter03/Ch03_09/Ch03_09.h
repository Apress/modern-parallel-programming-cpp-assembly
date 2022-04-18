//------------------------------------------------
//               Ch03_09.h
//------------------------------------------------

#pragma once
#include <vector>
#include "MatrixF64.h"

// Ch03_09_fcpp.cpp
extern std::vector<double> CalcColumnMeansF64_Cpp(const MatrixF64& x);
extern std::vector<double> CalcColumnMeansF64_Iavx(const MatrixF64& x);

// Miscellaneous constants
const unsigned int c_RngSeed = 41;
const double c_MatrixFillMin = 1.0;
const double c_MatrixFillMax = 80.0;
