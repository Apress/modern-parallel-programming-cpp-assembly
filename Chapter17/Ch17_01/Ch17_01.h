//------------------------------------------------
//               Ch17_01.h
//------------------------------------------------

#pragma once
#include <cstdint>
#include "ZmmVal.h"

// Ch17_01_fasm.asm.cpp
extern "C" void MathI16_Aavx512(ZmmVal c[6], const ZmmVal* a, const ZmmVal* b);
extern "C" void MathI64_Aavx512(ZmmVal c[6], const ZmmVal* a, const ZmmVal* b);

