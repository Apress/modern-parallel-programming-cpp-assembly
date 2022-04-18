//------------------------------------------------
//               Ch14_01.h
//------------------------------------------------

#pragma once
#include "YmmVal.h"

// Ch14_01_fcpp.cpp
extern "C" void PackedMathF32_Aavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
extern "C" void PackedMathF64_Aavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);

