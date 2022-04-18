//------------------------------------------------
//               Ch13_06.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <cstdint>

// Ch13_06_fcpp.cpp
extern bool CalcMeanU8_Cpp(double* mean_x, uint64_t* sum_x, const uint8_t* x, size_t n);

// Ch13_06_fasm.asm
extern "C" bool CalcMeanU8_Aavx(double* mean_x, uint64_t* sum_x, const uint8_t* x, size_t n);

// Ch13_06_misc.cpp
extern void InitArray(uint8_t* x, size_t n, unsigned int seed);
extern bool CheckArgs(const uint8_t* x, size_t n);

// Ch13_06_bm.cpp
extern void CalcMeanU8_bm(void);

// Miscellaneous constants
const size_t c_NumElements = 10000000;
const size_t c_Alignment = 16;
const unsigned int c_RngSeedVal = 29;
extern "C" size_t g_NumElementsMax;
