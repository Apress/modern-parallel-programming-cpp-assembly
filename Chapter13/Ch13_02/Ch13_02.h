//------------------------------------------------
//               Ch13_02.h
//------------------------------------------------

#pragma once
#include "XmmVal.h"

// Ch13_02_fasm.asm
extern "C" void MulI16_Aavx(XmmVal c[2], const XmmVal* a, const XmmVal* b);
extern "C" void MulI32a_Aavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
extern "C" void MulI32b_Aavx(XmmVal c[2], const XmmVal* a, const XmmVal* b);
