//------------------------------------------------
//               Ch15_01.h
//------------------------------------------------

#pragma once
#include "YmmVal.h"

// Ch15_01_fasm.asm
extern "C" void MathI16_Aavx2(YmmVal c[6], const YmmVal* a, const YmmVal* b);
extern "C" void MathI32_Aavx2(YmmVal c[6], const YmmVal* a, const YmmVal* b);
