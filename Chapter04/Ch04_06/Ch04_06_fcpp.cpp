//------------------------------------------------
//               Ch04_06_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <immintrin.h>
#include "Ch04_06.h"

inline uint64_t Sum_u32x8(__m256i x)
{
    uint64_t sum = _mm256_extract_epi32(x, 0);
    sum += _mm256_extract_epi32(x, 1);
    sum += _mm256_extract_epi32(x, 2);
    sum += _mm256_extract_epi32(x, 3);
    sum += _mm256_extract_epi32(x, 4);
    sum += _mm256_extract_epi32(x, 5);
    sum += _mm256_extract_epi32(x, 6);
    sum += _mm256_extract_epi32(x, 7);
    return sum;
}

inline __m256i SumMasked_u8x32(__m256i a_u8x32, __m256i mask_u8x32)
{
    __m256i vals_u8x32 =_mm256_and_si256(a_u8x32, mask_u8x32);

    __m128i vals_u8x16_0 = _mm256_extracti128_si256(vals_u8x32, 0);
    __m128i vals_u8x16_1 = _mm256_extracti128_si256(vals_u8x32, 1);

    __m256i vals_u32x8_0 = _mm256_cvtepu8_epi32(vals_u8x16_0);
    __m128i temp0 =  _mm_srli_si128(vals_u8x16_0, 8);
    __m256i vals_u32x8_1 = _mm256_cvtepu8_epi32(temp0);

    __m256i vals_u32x8_2 = _mm256_cvtepu8_epi32(vals_u8x16_1);
    __m128i temp1 = _mm_srli_si128(vals_u8x16_1, 8);
    __m256i vals_u32x8_3 = _mm256_cvtepu8_epi32(temp1);

    __m256i temp1_u32x8 = _mm256_add_epi32(vals_u32x8_0, vals_u32x8_1);
    __m256i temp2_u32x8 = _mm256_add_epi32(vals_u32x8_2, vals_u32x8_3);
    __m256i sum_u32x8 = _mm256_add_epi32(temp1_u32x8, temp2_u32x8);
    return sum_u32x8;
}

void ThresholdImage_Cpp(ITD* itd)
{
    uint8_t* pb_src = itd->m_PbSrc;
    uint8_t* pb_mask = itd->m_PbMask;
    uint8_t threshold = itd->m_Threshold;
    size_t num_pixels = itd->m_NumPixels;

    if (!CheckArgs(num_pixels, pb_src, pb_mask))
        throw std::runtime_error("ThreshholdImage_Cpp() - CheckArgs failed");

    // Threshold the image
    for (size_t i = 0; i < num_pixels; i++)
        *pb_mask++ = (*pb_src++ > threshold) ? 0xff : 0x00;
}

void ThresholdImage_Iavx2(ITD* itd)
{
    uint8_t* pb_src = itd->m_PbSrc;
    uint8_t* pb_mask = itd->m_PbMask;
    size_t num_pixels = itd->m_NumPixels;
    uint8_t threshold = itd->m_Threshold;
    const size_t num_simd_elements = c_NumSimdElements;

    if (!CheckArgs(num_pixels, pb_src, pb_mask))
        throw std::runtime_error("ThreshholdImage_Iavx2() - CheckArgs() failed");

    __m256i pixel_sf = _mm256_set1_epi8((char)0x80);
    __m256i pixel_threshold = _mm256_set1_epi8(threshold);
    __m256i pixel_threshold2 = _mm256_sub_epi8(pixel_threshold, pixel_sf);

    for (size_t i = 0; i < num_pixels; i += num_simd_elements)
    {
        // Load next block of 32 pixels
        __m256i pixel_vals_u8x32 = _mm256_load_si256((__m256i*)&pb_src[i]);

        // Calculate and save mask pixels
        pixel_vals_u8x32 = _mm256_sub_epi8(pixel_vals_u8x32, pixel_sf);

        __m256i mask_vals_u8x32 = _mm256_cmpgt_epi8(pixel_vals_u8x32, pixel_threshold2);
        _mm256_store_si256((__m256i*)&pb_mask[i], mask_vals_u8x32);
    }
}

void CalcImageMean_Cpp(ITD* itd)
{
    uint8_t* pb_src = itd->m_PbSrc;
    uint8_t* pb_mask = itd->m_PbMask;
    size_t num_pixels = itd->m_NumPixels;
    uint64_t sum_masked_pixels = 0;
    uint64_t num_masked_pixels = 0;

    for (size_t i = 0; i < num_pixels; i++)
    {
        uint8_t mask_val = *pb_mask++;
        num_masked_pixels += mask_val & 1;
        sum_masked_pixels += (*pb_src++ & mask_val);
    }

    itd->m_NumMaskedPixels = num_masked_pixels;
    itd->m_SumMaskedPixels = sum_masked_pixels;
    
    if (num_masked_pixels > 0)
        itd->m_MeanMaskedPixels = (double)sum_masked_pixels / num_masked_pixels;
    else
        itd->m_MeanMaskedPixels = -1.0;
}

void CalcImageMean_Iavx2(ITD* itd)
{
    uint8_t* pb_src = itd->m_PbSrc;
    uint8_t* pb_mask = itd->m_PbMask;
    size_t num_pixels = itd->m_NumPixels;
    const size_t num_simd_elements = c_NumSimdElements;

    __m256i count_mask_u8x32 = _mm256_set1_epi8(0x01);
    __m256i num_masked_pixels_u32x8 = _mm256_setzero_si256();
    __m256i sum_masked_pixels_u32x8 = _mm256_setzero_si256();

    for (size_t i = 0; i < num_pixels; i += num_simd_elements)
    {
        // Load the next block of 32 image pixels and the corresponding mask pixels
        __m256i pixel_vals_u8x32 = _mm256_load_si256((__m256i*)&pb_src[i]);
        __m256i mask_vals_u8x32 = _mm256_load_si256((__m256i*)&pb_mask[i]);

        // Update num_masked_pixels
        __m256i temp0 = SumMasked_u8x32(mask_vals_u8x32, count_mask_u8x32);
        num_masked_pixels_u32x8 = _mm256_add_epi32(num_masked_pixels_u32x8, temp0);

        // Update sum_masked_pixels
        __m256i temp1 = SumMasked_u8x32(pixel_vals_u8x32, mask_vals_u8x32);
        sum_masked_pixels_u32x8 = _mm256_add_epi32(sum_masked_pixels_u32x8, temp1);
    }

    // Calculate mean and save results
    uint64_t num_masked_pixels = Sum_u32x8(num_masked_pixels_u32x8);
    uint64_t sum_masked_pixels = Sum_u32x8(sum_masked_pixels_u32x8);
    itd->m_NumMaskedPixels = num_masked_pixels;
    itd->m_SumMaskedPixels = sum_masked_pixels;

    if (num_masked_pixels > 0)
         itd->m_MeanMaskedPixels = (double)sum_masked_pixels / num_masked_pixels;
    else
        itd->m_MeanMaskedPixels = -1;
}
