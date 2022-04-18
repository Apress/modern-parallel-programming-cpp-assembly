//------------------------------------------------
//               Ch08_02.h
//------------------------------------------------

#pragma once
#include <cstdint>
#include "ZmmVal.h"

// Ch08_02_fcpp.cpp
extern void PackedCompareF32_Iavx512(uint16_t c[8], const ZmmVal* a, const ZmmVal* b);
extern void PackedCompareF64_Iavx512(ZmmVal* c, const ZmmVal* a, const ZmmVal* b,
    double x1, double x2, double x3);
