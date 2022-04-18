//------------------------------------------------
//               Ch01_01.h
//------------------------------------------------

#pragma once

// Ch01_01_fcpp.cpp
extern void CalcZ_Cpp(float* z, const float* x, const float* y, size_t n);
extern void CalcZ_Iavx(float* z, const float* x, const float* y, size_t n);

// Ch01_01_fasm.asm
extern "C" void CalcZ_Aavx(float* z, const float* x, const float* y, size_t n);
