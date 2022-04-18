//------------------------------------------------
//               Ch03_05.h
//------------------------------------------------

#pragma once
#include <cstddef>

// Ch03_05_fcpp.cpp
extern bool CalcMeanF64_Cpp(double* mean, const double* x, size_t n);
extern bool CalcMeanF64_Iavx(double* mean, const double* x, size_t n);
extern bool CalcStDevF64_Cpp(double* st_dev, const double* x, size_t n, double mean);
extern bool CalcStDevF64_Iavx(double* st_dev, const double* x, size_t n, double mean);

// Ch03_05_misc.cpp
extern bool CheckArgs(const double* x, size_t n);
extern void InitArray(double* x, size_t n);

// Miscellaneous constants
const size_t c_NumElements = 91;
const unsigned int c_RngSeed = 13;
const double c_ArrayFillMin = 1.0;
const double c_ArrayFillMax = 100.0;
const size_t c_Alignment = 32;
