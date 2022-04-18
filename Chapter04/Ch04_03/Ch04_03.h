//------------------------------------------------
//               Ch04_03.h
//------------------------------------------------

#pragma once
#include "YmmVal.h"

// Ch04_03_fcpp.cpp
extern void ZeroExtU8_U16_Iavx2(YmmVal c[2], YmmVal* a);
extern void ZeroExtU8_U32_Iavx2(YmmVal c[4], YmmVal* a);
extern void SignExtI16_I32_Iavx2(YmmVal c[2], YmmVal* a);
extern void SignExtI16_I64_Iavx2(YmmVal c[4], YmmVal* a);

