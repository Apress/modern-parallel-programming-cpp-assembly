//------------------------------------------------
//               Ch11_03.h
//------------------------------------------------

#pragma once
#include <cstdint>

// Ch11_03_misc.cpp
extern void DisplayResultsDivI32(size_t test_id, int32_t rc, int32_t a,
    int32_t b, int32_t quo, int32_t rem);
extern void DisplayResultsDivU64(size_t test_id, int32_t rc, uint64_t a,
    uint64_t b, uint64_t quo, uint64_t rem);

// Ch11_03_fasm.asm
extern "C" int32_t DivI32_A(int32_t a, int32_t b, int32_t* quo, int32_t* rem);
extern "C" int32_t DivU64_A(uint64_t a, uint64_t b, uint64_t* quo, uint64_t* rem);
