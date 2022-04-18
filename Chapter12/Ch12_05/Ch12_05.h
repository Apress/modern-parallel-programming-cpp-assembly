//------------------------------------------------
//               Ch12_05.h
//------------------------------------------------

#pragma once

// Ch12_05_fcpp.cpp
extern bool CalcMeanF32_Cpp(float* mean, const float* x, size_t n);
extern bool CalcStDevF32_Cpp(float* st_dev, const float* x, size_t n, float mean);

// Ch12_05_fasm.asm
extern "C" bool CalcMeanF32_Aavx(float* mean, const float* x, size_t n);
extern "C" bool CalcStDevF32_Aavx(float* st_dev, const float* x, size_t n, float mean);

// Miscellaneous constants
const size_t c_NumElements = 91;
const unsigned int c_RngSeed = 13;
const float c_ArrayFillMin = 1.0f;
const float c_ArrayFillMax = 100.0f;
