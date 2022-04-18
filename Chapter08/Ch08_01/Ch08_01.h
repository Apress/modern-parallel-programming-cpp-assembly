//------------------------------------------------
//               Ch08_01.h
//------------------------------------------------

#pragma once
#include "ZmmVal.h"

// Ch08_01_fcpp.cpp
extern void PackedMathF32_Iavx512(ZmmVal c[8], const ZmmVal* a, const ZmmVal* b);
extern void PackedMathF64_Iavx512(ZmmVal c[8], const ZmmVal* a, const ZmmVal* b);
