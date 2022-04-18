//------------------------------------------------
//               Ch07_03.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <cstdint>
#include "ImageMisc.h"

// Ch07_03.cpp
extern const float c_Coef[4];
extern const char* c_TestImageFileName;

// Ch07_03_fcpp.cpp
extern void ConvertRgbToGs_Cpp(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4]);
extern void ConvertRgbToGs_Iavx512(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4]);

// Ch07_03_misc.cpp
extern bool CheckArgs(const uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4]);

// Ch07_03_bm.cpp
extern void ConvertRgbToGs_bm(void);
extern bool CompareGsPixelBuffers(const uint8_t* pb_gs1, const uint8_t* pb_gs2, size_t num_pixels);

// Miscellaneous constants
const size_t c_Alignment = 64;
const size_t c_NumPixelsMax = 256 * 1024 * 1024;
