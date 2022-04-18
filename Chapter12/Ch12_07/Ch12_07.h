//------------------------------------------------
//               Ch12_07.h
//------------------------------------------------

#pragma once
#include <cstdint>

// Ch12_07_fasm.asm
extern "C" void CalcSumProd_A(const int64_t* a, const int64_t* b, int32_t n,
    int64_t* sum_a, int64_t* sum_b, int64_t* prod_a, int64_t* prod_b);
