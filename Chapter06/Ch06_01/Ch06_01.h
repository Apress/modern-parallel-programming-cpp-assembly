//------------------------------------------------
//               Ch06_01.h
//------------------------------------------------

#pragma once
#include <vector>

// Ch06_01_fcpp.cpp
extern void Convolve1D_F32_Cpp(std::vector<float>& y,
    const std::vector<float>& x, const std::vector<float>& kernel);
extern void Convolve1D_F32_Iavx2(std::vector<float>& y,
    const std::vector<float>& x, const std::vector<float>& kernel);
extern void Convolve1DKs5_F32_Iavx2(std::vector<float>& y,
    const std::vector<float>& x, const std::vector<float>& kernel);

// Ch06_01_misc.cpp
extern bool CheckArgs(std::vector<float>& y,
    const std::vector<float>& x, const std::vector<float>& kernel);

// Ch06_01_bm.cpp
extern void Convolve1D_F32_bm(void);

// Miscellaneous constants
const unsigned int c_RngSeed = 97;
