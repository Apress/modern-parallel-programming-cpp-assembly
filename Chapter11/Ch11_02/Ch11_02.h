//------------------------------------------------
//               Ch11_02.h
//------------------------------------------------

#pragma once
#include <cstdint>

// Ch11_02_misc.cpp
extern void DisplayResultsMulI32(int32_t a, int32_t b, int32_t c, int32_t d);
extern void DisplayResultsMulU64(uint64_t a, uint64_t b, uint64_t c, uint64_t d);

// Ch11_02_fasm.asm
extern "C" int32_t MulI32_A(int32_t a, int32_t b, int32_t c);
extern "C" uint64_t MulU64_A(uint64_t a, uint64_t b, uint64_t c);
