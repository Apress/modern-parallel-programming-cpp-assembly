//------------------------------------------------
//               Ch03_03.h
//------------------------------------------------

#pragma once
#include "XmmVal.h"

enum class CvtOp : unsigned int
{
    I32_TO_F32, F32_TO_I32, I32_TO_F64, F64_TO_I32, F32_TO_F64, F64_TO_F32,
};

// Ch03_03_fcpp.cpp
extern void PackedConvertFP_Iavx(XmmVal* c, const XmmVal* a, CvtOp cvt_op);
