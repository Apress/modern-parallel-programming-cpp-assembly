//------------------------------------------------
//               Ch13_03.h
//------------------------------------------------

#pragma once
#include "XmmVal.h"

// Ch13_03_fasm.asm
extern "C" void AndU16_Aavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
extern "C" void OrU16_Aavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
extern "C" void XorU16_Aavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
