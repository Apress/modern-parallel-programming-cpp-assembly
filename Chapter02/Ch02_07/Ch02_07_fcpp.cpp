//------------------------------------------------
//               Ch02_07_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch02_07.h"

bool CalcMeanU8_Cpp(double* mean_x, uint64_t* sum_x, const uint8_t* x, size_t n)
{
    if (!CheckArgs(x, n))
        return false;

    uint64_t sum_x_temp = 0;

    for (size_t i = 0; i < n; i++)
        sum_x_temp += x[i];

    *sum_x = sum_x_temp;
    *mean_x = (double)sum_x_temp / n;
    return true;
}

bool CalcMeanU8_Iavx(double* mean_x, uint64_t* sum_x, const uint8_t* x, size_t n)
{
    if (!CheckArgs(x, n))
        return false;

    const size_t num_simd_elements = 16;

    __m128i packed_zero = _mm_setzero_si128();
    __m128i pixel_sums_u32 = _mm_setzero_si128();

    for (size_t i = 0; i < n; i += num_simd_elements * 4)
    {
        __m128i pixel_vals_u8, pixel_vals_lo_u16, pixel_vals_hi_u16;

        __m128i pixel_sums_u16 = _mm_setzero_si128();

        // Process pixels x[i:i+15]
        pixel_vals_u8 = _mm_load_si128((__m128i*)&x[i]);
        pixel_vals_lo_u16 = _mm_unpacklo_epi8(pixel_vals_u8, packed_zero);
        pixel_vals_hi_u16 = _mm_unpackhi_epi8(pixel_vals_u8, packed_zero);
        pixel_sums_u16 = _mm_add_epi16(pixel_sums_u16, pixel_vals_lo_u16);
        pixel_sums_u16 = _mm_add_epi16(pixel_sums_u16, pixel_vals_hi_u16);

        // Process pixels x[i+16:i+31]
        pixel_vals_u8 = _mm_load_si128((__m128i*)&x[i + 16]);
        pixel_vals_lo_u16 = _mm_unpacklo_epi8(pixel_vals_u8, packed_zero);
        pixel_vals_hi_u16 = _mm_unpackhi_epi8(pixel_vals_u8, packed_zero);
        pixel_sums_u16 = _mm_add_epi16(pixel_sums_u16, pixel_vals_lo_u16);
        pixel_sums_u16 = _mm_add_epi16(pixel_sums_u16, pixel_vals_hi_u16);

        // Process pixels x[i+32:i+47]
        pixel_vals_u8 = _mm_load_si128((__m128i*)&x[i + 32]);
        pixel_vals_lo_u16 = _mm_unpacklo_epi8(pixel_vals_u8, packed_zero);
        pixel_vals_hi_u16 = _mm_unpackhi_epi8(pixel_vals_u8, packed_zero);
        pixel_sums_u16 = _mm_add_epi16(pixel_sums_u16, pixel_vals_lo_u16);
        pixel_sums_u16 = _mm_add_epi16(pixel_sums_u16, pixel_vals_hi_u16);

        // Process pixels x[i+48:i+63]
        pixel_vals_u8 = _mm_load_si128((__m128i*)&x[i + 48]);
        pixel_vals_lo_u16 = _mm_unpacklo_epi8(pixel_vals_u8, packed_zero);
        pixel_vals_hi_u16 = _mm_unpackhi_epi8(pixel_vals_u8, packed_zero);
        pixel_sums_u16 = _mm_add_epi16(pixel_sums_u16, pixel_vals_lo_u16);
        pixel_sums_u16 = _mm_add_epi16(pixel_sums_u16, pixel_vals_hi_u16);

        // Convert pixel_sums_u16 to u32, then update pixel_sums_u32
        __m128i pixel_sums_lo_u32 = _mm_unpacklo_epi16(pixel_sums_u16, packed_zero);
        __m128i pixel_sums_hi_u32 = _mm_unpackhi_epi16(pixel_sums_u16, packed_zero);
        pixel_sums_u32 = _mm_add_epi32(pixel_sums_u32, pixel_sums_lo_u32);
        pixel_sums_u32 = _mm_add_epi32(pixel_sums_u32, pixel_sums_hi_u32);
    }

    // Reduce pixel_sums_u32 to single sum value
    uint64_t pixel_sum = _mm_extract_epi32(pixel_sums_u32, 0);
    pixel_sum += _mm_extract_epi32(pixel_sums_u32, 1);
    pixel_sum += _mm_extract_epi32(pixel_sums_u32, 2);
    pixel_sum += _mm_extract_epi32(pixel_sums_u32, 3);

    // Calculate mean
    *sum_x = pixel_sum;
    *mean_x = (double)pixel_sum / n;
    return true;
}
