//------------------------------------------------
//               Ch12_08.h
//------------------------------------------------

#pragma once

// Ch12_08_fcpp.cpp
extern bool CalcConeAreaVol_Cpp(const double* r, const double* h, int n,
    double* sa_cone, double* vol_cone);

// Ch12_08_fasm.asm
extern "C" bool CalcConeAreaVol_A(const double* r, const double* h, int n,
    double* sa_cone, double* vol_cone);
