//------------------------------------------------
//               Ch07_05.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <cstdint>

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

// Ch07_05.cpp
extern const char* c_ImageFileName;

// Ch07_05_fcpp.cpp
extern void CalcImageStats_Cpp(ImageStats& im_stats);
extern void CalcImageStats_Iavx512(ImageStats& im_stats);

// Ch07_05_misc.cpp
extern bool CheckArgs(const ImageStats& im_stats);

// Ch07_05_bm.cpp
extern void CalcImageStats_bm(void);

// Miscellaneous constants
const size_t c_Alignment = 64;
const size_t c_NumPixelsMax = 64 * 1024 * 1024;
const uint32_t c_PixelMinVal = 40;
const uint32_t c_PixelMaxVal = 230;
