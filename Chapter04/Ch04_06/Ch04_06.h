//------------------------------------------------
//               Ch04_06.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <cstdint>

struct ITD
{
    uint8_t* m_PbSrc;               // Source image pixel buffer
    uint8_t* m_PbMask;              // Mask mask pixel buffer
    size_t m_NumPixels;             // Number of source image pixels
    uint64_t m_NumMaskedPixels;     // Number of masked pixels
    uint64_t m_SumMaskedPixels;     // Sum of masked pixels
    double m_MeanMaskedPixels;      // Mean of masked pixels
    uint8_t m_Threshold;            // Image threshold value
};

// Ch04_06_fcpp.cpp
extern void ThresholdImage_Cpp(ITD* itd);
extern void ThresholdImage_Iavx2(ITD* itd);
extern void CalcImageMean_Cpp(ITD* itd);
extern void CalcImageMean_Iavx2(ITD* itd);

// Ch04_06_misc.cpp
extern bool CheckArgs(size_t num_pixels, const uint8_t* pb_src, const uint8_t* pb_mask);

// Ch04_06_bm.cpp
extern void ProcessImage_bm(void);

// Miscellaneous constants
const size_t c_Alignment = 32;
const size_t c_NumSimdElements = 32;
const size_t c_NumPixelsMax = 16 * 1024 * 1024;
const uint8_t c_TestThreshold = 224;
extern const char* c_TestImageFileName;
