//------------------------------------------------
//               Ch04_05_fcpp.cpp
//------------------------------------------------

#include <iostream>
#include <stdexcept>
#include <immintrin.h>
#include "Ch04_05.h"
#include "ImageMisc.h"

void ConvertRgbToGs_Cpp(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4])
{
    if (!CheckArgs(pb_gs, pb_rgb, num_pixels, coef))
        throw std::runtime_error("ConvertRgbToGs_Cpp() - CheckArgs failed");

    for (size_t i = 0; i < num_pixels; i++)
    {
        uint8_t r = pb_rgb[i].m_R;
        uint8_t g = pb_rgb[i].m_G;
        uint8_t b = pb_rgb[i].m_B;
        float gs_temp = r * coef[0] + g * coef[1] + b * coef[2] + 0.5f;

        if (gs_temp > 255.0f)
            gs_temp = 255.0f;

        pb_gs[i] = (uint8_t)gs_temp;
    }
}

void ConvertRgbToGs_Iavx2(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4])
{
    if (!CheckArgs(pb_gs, pb_rgb, num_pixels, coef))
        throw std::runtime_error("ConvertRgbToGs_Iavx2() - CheckArgs failed");

    __m256 packed_0p5_f32 = _mm256_set1_ps(0.5f);
    __m256 packed_255p0_f32 = _mm256_set1_ps(255.0f);
    __m256i packed_zero = _mm256_setzero_si256();
    __m256i u32_byte0_mask = _mm256_set1_epi32(0x000000ff);

    __m256 packed_coef_r = _mm256_set1_ps(coef[0]);
    __m256 packed_coef_g = _mm256_set1_ps(coef[1]);
    __m256 packed_coef_b = _mm256_set1_ps(coef[2]);

    const size_t num_simd_elements = 8;

    for (size_t i = 0; i < num_pixels; i += num_simd_elements)
    {
        // Load next block of eight RGB32 pixels
        __m256i pixel_vals = _mm256_load_si256((__m256i*)&pb_rgb[i]);

        // De-interleave color components and size promote to U32
        __m256i pixel_vals_r = pixel_vals;
        __m256i pixel_vals_g = _mm256_srli_epi32(pixel_vals, 8);
        __m256i pixel_vals_b = _mm256_srli_epi32(pixel_vals, 16);
        __m256i pixel_vals_r_u32 = _mm256_and_si256(pixel_vals_r, u32_byte0_mask);
        __m256i pixel_vals_g_u32 = _mm256_and_si256(pixel_vals_g, u32_byte0_mask);
        __m256i pixel_vals_b_u32 = _mm256_and_si256(pixel_vals_b, u32_byte0_mask);

        // Convert color components from U32 to F32
        __m256 pixel_vals_r_f32 = _mm256_cvtepi32_ps(pixel_vals_r_u32);
        __m256 pixel_vals_g_f32 = _mm256_cvtepi32_ps(pixel_vals_g_u32);
        __m256 pixel_vals_b_f32 = _mm256_cvtepi32_ps(pixel_vals_b_u32);

        // Multiply color components by conversion coefficients
        pixel_vals_r_f32 = _mm256_mul_ps(pixel_vals_r_f32, packed_coef_r);
        pixel_vals_g_f32 = _mm256_mul_ps(pixel_vals_g_f32, packed_coef_g);
        pixel_vals_b_f32 = _mm256_mul_ps(pixel_vals_b_f32, packed_coef_b);

        // Sum color components
        __m256 temp1_f32 = _mm256_add_ps(pixel_vals_r_f32, pixel_vals_g_f32);
        __m256 pixel_vals_gs_f32 = _mm256_add_ps(pixel_vals_b_f32, temp1_f32);

        // Clip grayscale pixel values
        pixel_vals_gs_f32 = _mm256_add_ps(pixel_vals_gs_f32, packed_0p5_f32);
        pixel_vals_gs_f32 = _mm256_min_ps(pixel_vals_gs_f32, packed_255p0_f32);

        // Convert grayscale values from F32 to U8
        __m256i pixel_vals_gs_u32 = _mm256_cvtps_epi32(pixel_vals_gs_f32);
        __m256i pixel_vals_gs_u16 = _mm256_packus_epi32(pixel_vals_gs_u32, packed_zero);
        __m256i temp2_u16 = _mm256_permute4x64_epi64(pixel_vals_gs_u16, 0b01011000);
        __m256i pixel_vals_gs_u8 = _mm256_packus_epi16(temp2_u16, packed_zero);

        // Save result to gs pixel buffer
        uint64_t gs_vals = _mm256_extract_epi64(pixel_vals_gs_u8, 0);
        *((uint64_t*)&pb_gs[i]) = gs_vals;
    }
}
