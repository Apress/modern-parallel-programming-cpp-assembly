//------------------------------------------------
//               Ch03_02.h
//------------------------------------------------

#pragma once
#include "YmmVal.h"

// Ch03_02_fcpp.cpp
extern void PackedCompareF32_Iavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
extern void PackedCompareF64_Iavx(YmmVal c[8], const YmmVal* a, const YmmVal* b);
