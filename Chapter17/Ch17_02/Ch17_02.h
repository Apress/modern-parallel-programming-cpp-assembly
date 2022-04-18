//------------------------------------------------
//               Ch17_02.h
//------------------------------------------------

#pragma once
#include <cstdint>
#include "ZmmVal.h"

// Ch07_02_fcpp.cpp
extern "C" void MaskOpI64a_Aavx512(ZmmVal c[5], uint8_t mask, const ZmmVal* a, const ZmmVal* b);
extern "C" void MaskOpI64b_Aavx512(ZmmVal c[5], uint8_t mask, const ZmmVal* a, const ZmmVal* b1, const ZmmVal* b2);
extern "C" void MaskOpI64c_Aavx512(ZmmVal* c, const ZmmVal* a, int64_t x1, int64_t x2);
