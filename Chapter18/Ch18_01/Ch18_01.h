//------------------------------------------------
//               Ch18_01.h
//------------------------------------------------

#pragma once
#include "ZmmVal.h"

// Ch18_01_fcpp.cpp
extern "C" void PackedMathF32_Aavx512(ZmmVal c[8], const ZmmVal* a, const ZmmVal* b);
extern "C" void PackedMathF64_Aavx512(ZmmVal c[8], const ZmmVal* a, const ZmmVal* b);
