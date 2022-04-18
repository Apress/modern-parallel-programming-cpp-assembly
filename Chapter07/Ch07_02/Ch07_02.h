//------------------------------------------------
//               Ch07_02.h
//------------------------------------------------

#pragma once
#include <cstdint>
#include "ZmmVal.h"

// Ch07_02_fcpp.cpp
extern void MaskOpI64a_Iavx512(ZmmVal c[5], uint8_t mask, const ZmmVal* a,
    const ZmmVal* b);
extern void MaskOpI64b_Iavx512(ZmmVal c[5], uint8_t mask, const ZmmVal* a,
    const ZmmVal* b1, const ZmmVal* b2);
extern void MaskOpI64c_Iavx512(ZmmVal* c, const ZmmVal* a, int64_t x1, int64_t x2);
