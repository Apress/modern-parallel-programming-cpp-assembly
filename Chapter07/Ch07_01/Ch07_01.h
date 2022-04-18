//------------------------------------------------
//               Ch07_01.h
//------------------------------------------------

#pragma once
#include <cstdint>
#include "ZmmVal.h"

// Ch07_01_fcpp.cpp
extern void MathI16_Iavx512(ZmmVal c[6], const ZmmVal* a, const ZmmVal* b);
extern void MathI64_Iavx512(ZmmVal c[6], const ZmmVal* a, const ZmmVal* b);
