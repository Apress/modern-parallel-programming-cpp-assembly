//------------------------------------------------
//               Ch03_06.h
//------------------------------------------------

#pragma once
#include <cstddef>

struct PointArrays
{
    float* X1;
    float* Y1;
    float* X2;
    float* Y2;
    float* Dist1;
    float* Dist2;
    float* DistCmp1;
    float* DistCmp2;
    size_t NumPoints;
};

// Ch03_06_fcpp.cpp
extern bool CalcDistancesF32_Cpp(PointArrays& pa);
extern bool CalcDistancesF32_Iavx(PointArrays& pa);
extern void CompareDistancesF32_Cpp(PointArrays& pa, float cmp_val);
extern void CompareDistancesF32_Iavx(PointArrays& pa, float cmp_val);

// Ch03_06_misc.cpp
extern bool CheckArgs(PointArrays& pa);
extern void FillPointArraysF32(PointArrays& pa, float min_val, float max_val, unsigned int rng_seed);

// Miscellaneous constants
const size_t c_NumPoints = 21;
const unsigned int c_RngSeed = 39;
const float c_ArrayFillMin = 1.0f;
const float c_ArrayFillMax = 75.0f;
const float c_CmpVal = 50.0f;
const size_t c_Alignment = 32;
