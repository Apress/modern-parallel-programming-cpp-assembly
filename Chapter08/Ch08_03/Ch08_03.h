//------------------------------------------------
//               Ch08_03.h
//------------------------------------------------

#pragma once
#include <cstddef>

// Ch08_03_fcpp.cpp
extern void CalcMeanF32_Cpp(float* mean, const float* x, size_t n);
extern void CalcMeanF32_Iavx512(float* mean, const float* x, size_t n);
extern void CalcStDevF32_Cpp(float* st_dev, const float* x, size_t n, float mean);
extern void CalcStDevF32_Iavx512(float* st_dev, const float* x, size_t n,
    float mean);

// Ch08_03_misc.cpp
extern bool CheckArgs(const float* x, size_t n);
extern void InitArray(float* x, size_t n);

// Miscellaneous constants
const size_t c_NumElements = 91;
const unsigned int c_RngSeed = 13;
const float c_ArrayFillMin = 1.0f;
const float c_ArrayFillMax = 100.0f;
const size_t c_Alignment = 64;
