//------------------------------------------------
//               Ch11_04.h
//------------------------------------------------

#pragma once
#include <cstdint>

// Ch11_04_fasm.asm
extern "C" int64_t CalcResultI64_A(int8_t a, int16_t b, int32_t c, int64_t d,
    int8_t e, int16_t f, int32_t g, int64_t h);

extern "C" int32_t CalcResultU64_A(uint8_t a, uint16_t b, uint32_t c, uint64_t d,
    uint8_t e, uint16_t f, uint32_t g, uint64_t h, uint64_t* quo, uint64_t* rem);
