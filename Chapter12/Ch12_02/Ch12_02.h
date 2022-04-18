//------------------------------------------------
//               Ch12_02.h
//------------------------------------------------

#pragma once

// Ch12_02_fcpp.cpp
extern double CalcDistance_Cpp(double x1, double y1, double z1, double x2,
    double y2, double z2);

// Ch12_02_fasm.asm
extern "C" double CalcDistance_Aavx(double x1, double y1, double z1, double x2,
    double y2, double z2);

// Ch12_02_misc.cpp
extern void InitArrays(double* x, double* y, double* z, size_t n,
    unsigned int rng_seed);
