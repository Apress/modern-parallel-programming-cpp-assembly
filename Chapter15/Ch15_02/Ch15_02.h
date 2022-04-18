//------------------------------------------------
//               Ch15_02.h
//------------------------------------------------

#pragma once
#include "YmmVal.h"

// Ch15_02_fcpp.cpp
extern "C" void ZeroExtU8_U16_Aavx2(YmmVal c[2], YmmVal* a);
extern "C" void ZeroExtU8_U32_Aavx2(YmmVal c[4], YmmVal* a);
extern "C" void SignExtI16_I32_Aavx2(YmmVal c[2], YmmVal* a);
extern "C" void SignExtI16_I64_Aavx2(YmmVal c[4], YmmVal* a);

