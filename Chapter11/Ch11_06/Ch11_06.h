//------------------------------------------------
//               Ch11_06.h
//------------------------------------------------

#pragma once

// Ch11_06_fcpp.cpp
extern int SumElementsI32_Cpp(const int* x, size_t n);

// Ch11_06_fasm.asm
extern "C" int SumElementsI32_A(const int* x, size_t n);

// Ch11_06_misc.cpp
extern void FillArray(int* x, size_t n);
extern void DisplayResults(const int* x, size_t n, int sum1, int sum2);
