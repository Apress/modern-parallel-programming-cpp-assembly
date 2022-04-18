//------------------------------------------------
//               Ch07_05_fcpp.cpp
//------------------------------------------------

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <immintrin.h>
#include "Ch07_05.h"

inline void CalcMeanStDev(ImageStats& im_stats)
{
    // Calculate mean and standard deviation
    double temp0 = (double)im_stats.m_NumPixelsInRange * im_stats.m_PixelSumSquares;
    double temp1 = (double)im_stats.m_PixelSum * im_stats.m_PixelSum;
    double var_num = temp0 - temp1;
    double var_den = (double)im_stats.m_NumPixelsInRange * (im_stats.m_NumPixelsInRange - 1);
    double var = var_num / var_den;

    im_stats.m_PixelMean = (double)im_stats.m_PixelSum / im_stats.m_NumPixelsInRange;
    im_stats.m_PixelStDev = sqrt(var);
}

void CalcImageStats_Cpp(ImageStats& im_stats)
{
    if (!CheckArgs(im_stats))
        throw std::runtime_error("CalcImageStats_Cpp() - CheckArgs failed");

    im_stats.m_PixelSum = 0;
    im_stats.m_PixelSumSquares = 0;
    im_stats.m_NumPixelsInRange = 0;

    size_t num_pixels = im_stats.m_NumPixels;
    const uint8_t* pb = im_stats.m_PixelBuffer;
 
    // Calculate intermediate sums
    for (size_t i = 0; i < num_pixels; i++)
    {
        uint32_t pval = pb[i];

        if (pval >= im_stats.m_PixelMinVal && pval <= im_stats.m_PixelMaxVal)
        {
            im_stats.m_PixelSum += pval;
            im_stats.m_PixelSumSquares += (uint64_t)pval * pval;
            im_stats.m_NumPixelsInRange++;
        }
    }

    CalcMeanStDev(im_stats);
}

inline uint64_t Sum_u64x8(__m512i x)
{
    return _mm512_reduce_add_epi64(x);
}

inline __m512i Add_u64x8_u32x16(__m512i x_u64x8, __m512i y_u32x16)
{
    // Add 32-bit integers in y to 64-bit integers in x
    __m256i temp0 = _mm512_extracti32x8_epi32(y_u32x16, 0);
    __m256i temp1 = _mm512_extracti32x8_epi32(y_u32x16, 1);
    __m256i temp2 = _mm256_add_epi32(temp0, temp1);
    __m512i temp3 = _mm512_cvtepu32_epi64(temp2);
    __m512i temp4 = _mm512_add_epi64(x_u64x8, temp3);
    return temp4;
}

void CalcImageStats_Iavx512(ImageStats& im_stats)
{
    if (!CheckArgs(im_stats))
        throw std::runtime_error("CalcImageStats_Iavx512() - CheckArgs failed");

    size_t num_pixels = im_stats.m_NumPixels;
    const uint8_t* pb = im_stats.m_PixelBuffer;

    __m512i pixel_min_vals = _mm512_set1_epi8((uint8_t)im_stats.m_PixelMinVal);
    __m512i pixel_max_vals = _mm512_set1_epi8((uint8_t)im_stats.m_PixelMaxVal);

    __m512i pixel_sums_u64x8 = _mm512_setzero_si512();
    __m512i pixel_sum_squares_u64x8 = _mm512_setzero_si512();

    uint64_t num_pixels_in_range = 0;
    const size_t num_simd_elements = 64;

    for (size_t i = 0; i < num_pixels; i += num_simd_elements)
    {
        // Load next block of 64 pixels
        __m512i pixel_vals = _mm512_load_si512(&pb[i]);

        // Calculate in-range pixels
        __mmask64 mask_ge_min = _mm512_cmpge_epu8_mask(pixel_vals, pixel_min_vals);
        __mmask64 mask_le_max = _mm512_cmple_epu8_mask(pixel_vals, pixel_max_vals);
        __mmask64 mask_in_range = _kand_mask64(mask_ge_min, mask_le_max);
        __m512i pixel_vals_in_range = _mm512_maskz_mov_epi8(mask_in_range, pixel_vals);

        num_pixels_in_range += _mm_popcnt_u64(mask_in_range);

        // Calculate pixel_sums and pixel_sum_squares for current block
        __m128i pixel_vals_u8x16;
        __m512i pixel_vals_u32x16;
        __m512i pixel_sums_u32x16 = _mm512_setzero_si512();
        __m512i pixel_sum_squares_u32x16 = _mm512_setzero_si512();

        pixel_vals_u8x16 = _mm512_extracti64x2_epi64(pixel_vals_in_range, 0);
        pixel_vals_u32x16 = _mm512_cvtepu8_epi32(pixel_vals_u8x16);
        pixel_sums_u32x16 = _mm512_add_epi32(pixel_sums_u32x16, pixel_vals_u32x16);
        pixel_vals_u32x16 = _mm512_mullo_epi32(pixel_vals_u32x16, pixel_vals_u32x16);
        pixel_sum_squares_u32x16 = _mm512_add_epi32(pixel_sum_squares_u32x16, pixel_vals_u32x16);

        pixel_vals_u8x16 = _mm512_extracti64x2_epi64(pixel_vals_in_range, 1);
        pixel_vals_u32x16 = _mm512_cvtepu8_epi32(pixel_vals_u8x16);
        pixel_sums_u32x16 = _mm512_add_epi32(pixel_sums_u32x16, pixel_vals_u32x16);
        pixel_vals_u32x16 = _mm512_mullo_epi32(pixel_vals_u32x16, pixel_vals_u32x16);
        pixel_sum_squares_u32x16 = _mm512_add_epi32(pixel_sum_squares_u32x16, pixel_vals_u32x16);

        pixel_vals_u8x16 = _mm512_extracti64x2_epi64(pixel_vals_in_range, 2);
        pixel_vals_u32x16 = _mm512_cvtepu8_epi32(pixel_vals_u8x16);
        pixel_sums_u32x16 = _mm512_add_epi32(pixel_sums_u32x16, pixel_vals_u32x16);
        pixel_vals_u32x16 = _mm512_mullo_epi32(pixel_vals_u32x16, pixel_vals_u32x16);
        pixel_sum_squares_u32x16 = _mm512_add_epi32(pixel_sum_squares_u32x16, pixel_vals_u32x16);

        pixel_vals_u8x16 = _mm512_extracti64x2_epi64(pixel_vals_in_range, 3);
        pixel_vals_u32x16 = _mm512_cvtepu8_epi32(pixel_vals_u8x16);
        pixel_sums_u32x16 = _mm512_add_epi32(pixel_sums_u32x16, pixel_vals_u32x16);
        pixel_vals_u32x16 = _mm512_mullo_epi32(pixel_vals_u32x16, pixel_vals_u32x16);
        pixel_sum_squares_u32x16 = _mm512_add_epi32(pixel_sum_squares_u32x16, pixel_vals_u32x16);

        // Update uint64_t sums and sum_squares
        pixel_sums_u64x8 = Add_u64x8_u32x16(pixel_sums_u64x8, pixel_sums_u32x16);
        pixel_sum_squares_u64x8 = Add_u64x8_u32x16(pixel_sum_squares_u64x8, pixel_sum_squares_u32x16);
    }

    // Perform reductions
    im_stats.m_PixelSum = Sum_u64x8(pixel_sums_u64x8);
    im_stats.m_PixelSumSquares = Sum_u64x8(pixel_sum_squares_u64x8);
    im_stats.m_NumPixelsInRange = num_pixels_in_range;

    // Calculate mean and SD
    CalcMeanStDev(im_stats);
}
