//------------------------------------------------
//               Ch11_07.h
//------------------------------------------------

#pragma once

// Ch11_07_fasm.asm
extern "C" int SignedMin1_A(int a, int b, int c);
extern "C" int SignedMin2_A(int a, int b, int c);
extern "C" int SignedMax1_A(int a, int b, int c);
extern "C" int SignedMax2_A(int a, int b, int c);

// Ch11_07_misc.cpp
void DisplayResult(const char* s1, int a, int b, int c, int result);
