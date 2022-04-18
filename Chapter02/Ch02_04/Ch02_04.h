//------------------------------------------------
//               Ch02_04.h
//------------------------------------------------

#pragma once
#include "XmmVal.h"

// Ch02_04_fcpp.cpp
extern void AndU16_Iavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
extern void OrU16_Iavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
extern void XorU16_Iavx(XmmVal* c, const XmmVal* a, const XmmVal* b);
