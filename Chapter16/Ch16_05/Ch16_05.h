//------------------------------------------------
//               Ch16_05.h
//------------------------------------------------

#pragma once
#include <vector>

// Ch16_05_fcpp.cpp
extern void Convolve1D_F32_Cpp(std::vector<float>& y, const std::vector<float>& x, const std::vector<float>& kernel);

// Ch16_05_fasm.asm.cpp
extern "C" void Convolve1D_F32_Aavx2(float* y, const float* x, const float* kernel, size_t num_pts, size_t kernel_size);
extern "C" void Convolve1DKs5_F32_Aavx2(float* y, const float* x, const float* kernel, size_t num_pts);

// Ch16_05_misc.cpp
extern bool CheckArgs(std::vector<float>& y, const std::vector<float>& x, const std::vector<float>& kernel);

// Ch16_05_bm.cpp
extern void Convolve1D_F32_bm(void);

// Miscellaneous constants
const unsigned int c_RngSeed = 97;
