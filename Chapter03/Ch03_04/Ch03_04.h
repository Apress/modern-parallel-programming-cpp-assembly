//------------------------------------------------
//               Ch03_04.h
//------------------------------------------------

#pragma once
#include <cstddef>

// Ch03_04_fcpp.cpp
extern bool CalcMeanF32_Cpp(float* mean, const float* x, size_t n);
extern bool CalcStDevF32_Cpp(float* st_dev, const float* x, size_t n, float mean);
extern bool CalcMeanF32_Iavx(float* mean, const float* x, size_t n);
extern bool CalcStDevF32_Iavx(float* st_dev, const float* x, size_t n, float mean);

// Ch03_04_misc.cpp
extern bool CheckArgs(const float* x, size_t n);
extern void InitArray(float* x, size_t n);

// Miscellaneous constants
const size_t c_NumElements = 91;
const unsigned int c_RngSeed = 13;
const float c_ArrayFillMin = 1.0f;
const float c_ArrayFillMax = 100.0f;
const size_t c_Alignment = 32;
