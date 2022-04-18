//------------------------------------------------
//               Ch14_02.h
//------------------------------------------------

#pragma once
#include "YmmVal.h"

// Ch14_02_fasm.cpp
extern "C" void PackedCompareF32_Aavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
extern "C" void PackedCompareF64_Aavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
