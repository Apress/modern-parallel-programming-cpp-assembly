//------------------------------------------------
//               Ch16_01.h
//------------------------------------------------

#pragma once

// Ch16_01_fcpp.cpp
extern void CalcLeastSquares_Cpp(double* m, double* b, const double* x, const double* y, size_t n);

// Ch16_01_fasm.asm
extern "C" void CalcLeastSquares_Aavx2(double* m, double* b, const double* x, const double* y, size_t n);

// Ch16_01_misc.cpp
extern bool CheckArgs(const double* x, const double* y, size_t n);
extern void FillArrays(double* x, double* y, size_t n);

// Miscellaneous constants
const size_t c_Alignment = 32;
const double c_LsEpsilon = 1.0e-12;
extern "C" double g_LsEpsilon;
