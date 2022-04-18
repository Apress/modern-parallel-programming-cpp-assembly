//------------------------------------------------
//               Ch17_04.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <cstdint>

// Simple image statistics structure. This must match the structure that's
// defined in Ch17_04_fasm.asm
struct ImageStats
{
    uint8_t* m_PixelBuffer;
    uint32_t m_PixelMinVal;
    uint32_t m_PixelMaxVal;
    size_t m_NumPixels;
    size_t m_NumPixelsInRange;
    uint64_t m_PixelSum;
    uint64_t m_PixelSumSquares;
    double m_PixelMean;
    double m_PixelStDev;
};

// Ch17_04.cpp
extern const char* c_ImageFileName;

// Ch17_04_fcpp.cpp
extern void CalcImageStats_Cpp(ImageStats& im_stats);

// Ch17_04_fasm.cpp
extern "C" void CalcImageStats_Aavx512(ImageStats& im_stats);

// Ch17_04_misc.cpp
extern "C" bool CheckArgs(const ImageStats& im_stats);

// Ch17_04_bm.cpp
extern void CalcImageStats_bm(void);

// Miscellaneous constants
const size_t c_Alignment = 64;
const size_t c_NumPixelsMax = 64 * 1024 * 1024;
const uint32_t c_PixelMinVal = 40;
const uint32_t c_PixelMaxVal = 230;
