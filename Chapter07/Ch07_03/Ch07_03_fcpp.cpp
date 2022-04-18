//------------------------------------------------
//               Ch07_03_fcpp.cpp
//------------------------------------------------

#include <iostream>
#include <stdexcept>
#include <immintrin.h>
#include "Ch07_03.h"
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

void ConvertRgbToGs_Iavx512(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4])
{
    if (!CheckArgs(pb_gs, pb_rgb, num_pixels, coef))
        throw std::runtime_error("ConvertRgbToGs_Iavx512() - CheckArgs failed");

    __m512 packed_0p5_f32 = _mm512_set1_ps(0.5f);
    __m512 packed_255p0_f32 = _mm512_set1_ps(255.0f);
    __m512i u32_byte0_mask = _mm512_set1_epi32(0x000000ff);

    __m512 packed_coef_r = _mm512_set1_ps(coef[0]);
    __m512 packed_coef_g = _mm512_set1_ps(coef[1]);
    __m512 packed_coef_b = _mm512_set1_ps(coef[2]);

    const size_t num_simd_elements = 16;

    for (size_t i = 0; i < num_pixels; i += num_simd_elements)
    {
        // Load next block of sixteen RGB32 pixels
        __m512i pixel_vals = _mm512_load_si512((__m512i*)&pb_rgb[i]);

        // De-interleave color components and size promote to U32
        __m512i pixel_vals_r = pixel_vals;
        __m512i pixel_vals_g = _mm512_srli_epi32(pixel_vals, 8);
        __m512i pixel_vals_b = _mm512_srli_epi32(pixel_vals, 16);
        __m512i pixel_vals_r_u32 = _mm512_and_si512(pixel_vals_r, u32_byte0_mask);
        __m512i pixel_vals_g_u32 = _mm512_and_si512(pixel_vals_g, u32_byte0_mask);
        __m512i pixel_vals_b_u32 = _mm512_and_si512(pixel_vals_b, u32_byte0_mask);

        // Convert color components from U32 to F32
        __m512 pixel_vals_r_f32 = _mm512_cvtepi32_ps(pixel_vals_r_u32);
        __m512 pixel_vals_g_f32 = _mm512_cvtepi32_ps(pixel_vals_g_u32);
        __m512 pixel_vals_b_f32 = _mm512_cvtepi32_ps(pixel_vals_b_u32);

        // Multiply color components by conversion coefficients
        pixel_vals_r_f32 = _mm512_mul_ps(pixel_vals_r_f32, packed_coef_r);
        pixel_vals_g_f32 = _mm512_mul_ps(pixel_vals_g_f32, packed_coef_g);
        pixel_vals_b_f32 = _mm512_mul_ps(pixel_vals_b_f32, packed_coef_b);

        // Sum color components
        __m512 temp1_f32 = _mm512_add_ps(pixel_vals_r_f32, pixel_vals_g_f32);
        __m512 pixel_vals_gs_f32 = _mm512_add_ps(pixel_vals_b_f32, temp1_f32);

        // Round and clip grayscale pixel values
        pixel_vals_gs_f32 = _mm512_add_ps(pixel_vals_gs_f32, packed_0p5_f32);
        pixel_vals_gs_f32 = _mm512_min_ps(pixel_vals_gs_f32, packed_255p0_f32);

        // Convert from F32 to U8
        __m512i pixel_vals_gs_u32 = _mm512_cvtps_epi32(pixel_vals_gs_f32);
        __m128i pixel_vals_gs_u8 = _mm512_cvtusepi32_epi8(pixel_vals_gs_u32);

        // Save sixteen gray scale pixels
        _mm_store_si128((__m128i*)&pb_gs[i], pixel_vals_gs_u8);
    }
}
