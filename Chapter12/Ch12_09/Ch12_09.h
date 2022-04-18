//------------------------------------------------
//               Ch12_09.h
//------------------------------------------------

#pragma once

// Ch12_09_fcpp.cpp
extern bool CalcBSA_Cpp(const double* ht, const double* wt, int n,
    double* bsa1, double* bsa2, double* bsa3);

// Ch12_09_fasm.asm
extern "C" bool CalcBSA_Aavx(const double* ht, const double* wt, int n,
    double* bsa1, double* bsa2, double* bsa3);
