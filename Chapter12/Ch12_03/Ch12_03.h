//------------------------------------------------
//               Ch12_03.h
//------------------------------------------------

#pragma once
#include <cstdint>

// Ch12_03_fasm.asm
extern "C" void CompareF32_Aavx(float a, float b, uint8_t* results);

// Ch12_03_misc.cpp
extern void DisplayResults(float a, float b, const uint8_t* cmp_results);

// Miscellaenous constants
const size_t c_NumCmpOps = 7;
