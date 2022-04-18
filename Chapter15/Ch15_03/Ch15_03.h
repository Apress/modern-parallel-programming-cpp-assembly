//------------------------------------------------
//               Ch15_03.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <cstdint>

// The members of ClipData must match the corresponding structure
// that's declared in Ch15_03_fasm.asm

struct ClipData
{
    uint8_t* m_PbSrc;               // source buffer pointer
    uint8_t* m_PbDes;               // destination buffer pointer
    size_t m_NumPixels;             // number of pixels
    size_t m_NumClippedPixels;      // number of clipped pixels
    uint8_t m_ThreshLo;             // low threshold
    uint8_t m_ThreshHi;             // high threshold
};

// Ch15_03_fcpp.cpp
extern void ClipPixels_Cpp(ClipData* clip_data);

// Ch15_03_fasm.asm
extern "C" void ClipPixels_Aavx2(ClipData* clip_data);

// Ch15_03_misc.cpp
extern bool CheckArgs(const ClipData* clip_data);

// Ch15_03_bm.cpp
extern void ClipPixels_bm(void);

// Miscellaneous constants
const size_t c_Alignment = 32;
const int c_RngMinVal = 0;
const int c_RngMaxVal = 255;
const unsigned int c_RngSeed = 157;
const uint8_t c_ThreshLo = 10;
const uint8_t c_ThreshHi = 245;
const size_t c_NumPixels = 8 * 1024 * 1024 + 31;
const size_t c_NumPixelsBM = 10000000;

