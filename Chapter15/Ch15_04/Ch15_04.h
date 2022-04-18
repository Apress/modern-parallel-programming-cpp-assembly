//------------------------------------------------
//               Ch15_04.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <cstdint>
#include "ImageMisc.h"

// Ch15_04.cpp
extern const float c_Coef[4];
extern const char* c_TestImageFileName;

// Ch15_04_fcpp.cpp
extern void ConvertRgbToGs_Cpp(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4]);

// Ch15_04_fasm.asm
extern "C" void ConvertRgbToGs_Aavx2(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4]);

// Ch15_04_misc.cpp
extern bool CheckArgs(const uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4]);

// Ch15_04_bm.cpp
extern void ConvertRgbToGs_bm(void);
extern bool CompareGsPixelBuffers(const uint8_t* pb_gs1, const uint8_t* pb_gs2, size_t num_pixels);

// Miscellaneous constants
const size_t c_Alignment = 32;
const size_t c_NumPixelsMax = 256 * 1024 * 1024;
extern "C" size_t g_NumPixelsMax;

