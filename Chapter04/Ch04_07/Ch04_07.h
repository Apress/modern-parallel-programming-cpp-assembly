//------------------------------------------------
//               Ch04_07.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <cstdint>

// Ch04_07_fcpp.cpp
extern void ConvertU8ToF32_Cpp(float* pb_des, const uint8_t* pb_src, size_t num_pixels);
extern void ConvertU8ToF32_Iavx2(float* pb_des, const uint8_t* pb_src, size_t num_pixels);

// Ch04_07_misc.cpp
extern void BuildLUT_U8ToF32(void);
extern bool CheckArgs(const void* pb1, const void* pb2, size_t num_pixels);
extern size_t CompareArraysF32(const float* pb_src1, const float* pb_src2, size_t num_pixels);

// Ch04_07_bm.cpp
extern void ConvertU8ToF32_bm(void);

// Miscellaneous constants
const size_t c_Alignment = 32;
const size_t c_NumPixels = 1024 * 1024 + 19;
const size_t c_NumPixelsBM = 10000000;
const size_t c_NumPixelsMax = 16 * 1024 * 1024;
const int c_FillMinVal = 0;
const int c_FillMaxVal = 255;
const unsigned int c_RngSeed = 71;
extern float g_LUT_U8ToF32[]; 
