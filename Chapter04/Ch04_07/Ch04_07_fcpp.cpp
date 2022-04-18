//------------------------------------------------
//               Ch04_07_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <immintrin.h>
#include "Ch04_07.h"

void ConvertU8ToF32_Cpp(float* pb_des, const uint8_t* pb_src, size_t num_pixels)
{
    if (!CheckArgs(pb_des, pb_src, num_pixels))
        throw std::runtime_error("ConvertU8ToF32_Cpp() CheckArgs failed");

    const float* lut = g_LUT_U8ToF32;

    for (size_t i = 0; i < num_pixels; i++)
        pb_des[i] = lut[pb_src[i]];
}

void ConvertU8ToF32_Iavx2(float* pb_des, const uint8_t* pb_src, size_t num_pixels)
{
    if (!CheckArgs(pb_des, pb_src, num_pixels))
        throw std::runtime_error("ConvertU8ToF32_Iavx2() CheckArgs failed");

    size_t i = 0;
    const size_t num_simd_elements = 32;
    const float* lut = g_LUT_U8ToF32;

    for (; num_pixels - i >= num_simd_elements; i += num_simd_elements)
    {
        // Load next block of 32 pixels
        __m256i pixel_vals_u8x32 = _mm256_load_si256((__m256i*)&pb_src[i]);
        __m128i pixel_vals_u8x16_0 = _mm256_extracti128_si256(pixel_vals_u8x32, 0);
        __m128i pixel_vals_u8x16_1 = _mm256_extracti128_si256(pixel_vals_u8x32, 1);

        // Convert pixels pb_src[0:15] from U8 to F32
        __m256i pixel_vals_u32x8_0 = _mm256_cvtepu8_epi32(pixel_vals_u8x16_0);
        __m256 pixel_vals_f32x8_0 = _mm256_i32gather_ps(lut, pixel_vals_u32x8_0, 4);
        __m128i temp0 =  _mm_srli_si128(pixel_vals_u8x16_0, 8);
        __m256i pixel_vals_u32x8_1 = _mm256_cvtepu8_epi32(temp0);
        __m256 pixel_vals_f32x8_1 = _mm256_i32gather_ps(lut, pixel_vals_u32x8_1, 4);

        // Convert pixels pb_src[16:31] from U8 to F32
        __m256i pixel_vals_u32x8_2 = _mm256_cvtepu8_epi32(pixel_vals_u8x16_1);
        __m256 pixel_vals_f32x8_2 = _mm256_i32gather_ps(lut, pixel_vals_u32x8_2, 4);
        __m128i temp1 = _mm_srli_si128(pixel_vals_u8x16_1, 8);
        __m256i pixel_vals_u32x8_3 = _mm256_cvtepu8_epi32(temp1);
        __m256 pixel_vals_f32x8_3 = _mm256_i32gather_ps(lut, pixel_vals_u32x8_3, 4);

        // Save results
        _mm256_store_ps(&pb_des[i], pixel_vals_f32x8_0);
        _mm256_store_ps(&pb_des[i + 8], pixel_vals_f32x8_1);
        _mm256_store_ps(&pb_des[i + 16], pixel_vals_f32x8_2);
        _mm256_store_ps(&pb_des[i + 24], pixel_vals_f32x8_3);
    }

    // Process final block of pixels
    for (; i < num_pixels; i++)
        pb_des[i] = lut[pb_src[i]];
}
