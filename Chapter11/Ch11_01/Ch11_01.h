//------------------------------------------------
//               Ch11_01.h
//------------------------------------------------

#pragma once

// Ch11_01_misc.cpp
extern void DisplayResultsAddI32(int a, int b, int c, int d);
extern void DisplayResultsSubI64(long long a, long long b, long long c, long long d);

// Ch11_01_fasm.asm
extern "C" int AddI32_A(int a, int b, int c);
extern "C" long long SubI64_A(long long a, long long b, long long c);
