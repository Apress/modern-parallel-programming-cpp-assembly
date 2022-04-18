//------------------------------------------------
//               Ch03_01.h
//------------------------------------------------

#pragma once
#include "YmmVal.h"

// Ch03_01_fcpp.cpp
extern void PackedMathF32_Iavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
extern void PackedMathF64_Iavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
