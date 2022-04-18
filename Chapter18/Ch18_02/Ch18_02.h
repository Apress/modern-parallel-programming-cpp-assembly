//------------------------------------------------
//               Ch18_02.h
//------------------------------------------------

#pragma once
#include "ZmmVal.h"

// Ch18_02_fcpp.cpp
extern "C" void PackedCompareF32_Aavx512(uint16_t c[8], const ZmmVal* a, const ZmmVal* b);
extern "C" void PackedCompareF64_Aavx512(uint8_t c[8], const ZmmVal* a, const ZmmVal* b);
