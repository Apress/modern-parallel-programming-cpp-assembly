//------------------------------------------------
//               Ch04_01.h
//------------------------------------------------

#pragma once
#include "YmmVal.h"

// Ch04_01_fcpp.cpp
extern void MathI16_Iavx2(YmmVal c[6], const YmmVal* a, const YmmVal* b);
extern void MathI32_Iavx2(YmmVal c[6], const YmmVal* a, const YmmVal* b);
