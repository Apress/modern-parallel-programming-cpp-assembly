//------------------------------------------------
//               Ch13_01.h
//------------------------------------------------

#pragma once
#include "XmmVal.h"

// Ch13_01_fasm.asm
extern "C" void AddI16_Aavx(XmmVal* c1, XmmVal* c2, const XmmVal* a, const XmmVal* b);
extern "C" void SubI16_Aavx(XmmVal* c1, XmmVal* c2, const XmmVal* a, const XmmVal* b);
