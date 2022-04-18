//------------------------------------------------
//               Ch14_05.h
//------------------------------------------------

#pragma once

// Ch14_05_fcpp.cpp
extern void CalcColumnMeansF64_Cpp(double* col_means, const double* x, size_t nrows,
    size_t ncols);

// Ch14_04_fasm.asm
extern "C" void CalcColumnMeansF64_Aavx(double* col_means, const double* x,
    size_t nrows, size_t ncols);

// Miscellaneous constants
const unsigned int c_RngSeed = 41;
const double c_MatrixFillMin = 1.0;
const double c_MatrixFillMax = 80.0;
