//------------------------------------------------
//               Ch13_04.h
//------------------------------------------------

#pragma once
#include "XmmVal.h"

// Ch13_04_fasm.asm
extern "C" void SllU16_Aavx(XmmVal* c, const XmmVal* a, int count);
extern "C" void SrlU16_Aavx(XmmVal* c, const XmmVal* a, int count);
extern "C" void SraU16_Aavx(XmmVal* c, const XmmVal* a, int count);
