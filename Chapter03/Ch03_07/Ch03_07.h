//------------------------------------------------
//               Ch03_07.h
//------------------------------------------------

#pragma once
#include <cstddef>

struct PointArrays
{
    double* X1;
    double* Y1;
    double* X2;
    double* Y2;
    double* Dist1;
    double* Dist2;
    double* DistCmp1;
    double* DistCmp2;
    size_t NumPoints;
};

// Ch03_07_fcpp.cpp
extern bool CalcDistancesF64_Cpp(PointArrays& pa);
extern bool CalcDistancesF64_Iavx(PointArrays& pa);
extern void CompareDistancesF64_Cpp(PointArrays& pa, double cmp_val);
extern void CompareDistancesF64_Iavx(PointArrays& pa, double cmp_val);

// Ch03_07_misc.cpp
extern bool CheckArgs(PointArrays& pa);
extern void FillPointArraysF64(PointArrays& pa, double min_val, double max_val, unsigned int rng_seed);

// Miscellaneous constants
const size_t c_NumPoints = 21;
const unsigned int c_RngSeed = 39;
const double c_ArrayFillMin = 1.0;
const double c_ArrayFillMax = 75.0;
const double c_CmpVal = 50.0;
const size_t c_Alignment = 32;
