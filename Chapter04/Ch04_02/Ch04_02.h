//------------------------------------------------
//               Ch04_02.h
//------------------------------------------------

#pragma once
#include "YmmVal.h"

// Ch04_02_fcpp.cpp
extern void UnpackU32_U64_Iavx2(YmmVal c[2], const YmmVal* a, const YmmVal* b);
extern void PackI32_I16_Iavx2(YmmVal* c, const YmmVal* a, const YmmVal* b);
