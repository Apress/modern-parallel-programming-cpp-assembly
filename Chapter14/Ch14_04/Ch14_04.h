//------------------------------------------------
//               Ch14_04.h
//------------------------------------------------

#pragma once

// The members of PA below must match the PA structure
// that's declared in Ch14_04_fasm.asm

struct PA
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

// Ch14_04_fcpp.cpp
extern bool CalcDistancesF64(PA& pa);
extern void CompareDistancesF64(PA& pa, double cmp_val);

// Ch14_04_fasm.asm
extern "C" bool CalcDistancesF64_Aavx(PA& pa);
extern "C" void CompareDistancesF64_Aavx(PA& pa, const double* cmp_val);

// Ch14_04_misc.cpp
extern "C" bool CheckArgs(PA& pa);
extern void FillPAF64(PA& pa, double min_val, double max_val, unsigned int rng_seed);

// Miscellaneous constants
const size_t c_NumPoints = 21;
const unsigned int c_RngSeed = 39;
const double c_ArrayFillMin = 1.0;
const double c_ArrayFillMax = 75.0;
const double c_CmpVal = 50.0;
const size_t c_Alignment = 32;

