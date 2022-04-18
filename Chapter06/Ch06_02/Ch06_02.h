//------------------------------------------------
//               Ch06_02.h
//------------------------------------------------

#pragma once
#include <vector>

// Ch06_02_fcpp.cpp
extern void Convolve1D_F64_Cpp(std::vector<double>& y,
    const std::vector<double>& x, const std::vector<double>& kernel);
extern void Convolve1D_F64_Iavx2(std::vector<double>& y,
    const std::vector<double>& x, const std::vector<double>& kernel);
extern void Convolve1DKs5_F64_Iavx2(std::vector<double>& y,
    const std::vector<double>& x, const std::vector<double>& kernel);

// Ch06_02_misc.cpp
extern bool CheckArgs(std::vector<double>& y,
    const std::vector<double>& x, const std::vector<double>& kernel);

// Ch06_02_bm.cpp
extern void Convolve1D_F64_bm(void);

// Miscellaneous constants
const unsigned int c_RngSeed = 97;
