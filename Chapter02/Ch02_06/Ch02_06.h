//------------------------------------------------
//               Ch02_06.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <cstdint>

// Ch02_06_fcpp.cpp
extern bool CalcMinMaxU8_Cpp(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, size_t n);
extern bool CalcMinMaxU8_Iavx(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, size_t n);

// Ch02_06_misc.cpp
extern void InitArray(uint8_t* x, size_t n, unsigned int rng_seed);

// Ch02_06_BM.cpp
extern void CalcMinMaxU8_bm();

// c_NumElements must be > 0 and even multiple of 16
const size_t c_NumElements = 10000000;
const unsigned int c_RngSeedVal = 23;
