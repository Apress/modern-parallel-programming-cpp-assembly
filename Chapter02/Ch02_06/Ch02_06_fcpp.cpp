//------------------------------------------------
//               Ch02_06_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch02_06.h"
#include "AlignedMem.h"

bool CalcMinMaxU8_Cpp(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, size_t n)
{
    if (n == 0 || ((n % 16) != 0))
        return false;

    if (!AlignedMem::IsAligned(x, 16))
        return false;

    uint8_t min_val = 0xff;
    uint8_t max_val = 0;

    for (size_t i = 0; i < n; i++)
    {
        uint8_t x_val = x[i];

        if (x_val < min_val)
            min_val = x_val;
        else if (x_val > max_val)
            max_val = x_val;
    }

    *x_min = min_val;
    *x_max = max_val;
    return true;
}

bool CalcMinMaxU8_Iavx(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, size_t n)
{
    if (n == 0 || ((n % 16) != 0))
        return false;

    if (!AlignedMem::IsAligned(x, 16))
        return false;

    __m128i min_vals = _mm_set1_epi8((char)0xff);
    __m128i max_vals = _mm_setzero_si128();

    const size_t num_simd_elements = 16;

    for (size_t i = 0; i < n; i += num_simd_elements)
    {
        __m128i x_vals = _mm_load_si128((__m128i*)&x[i]);

        min_vals = _mm_min_epu8(x_vals, min_vals);
        max_vals = _mm_max_epu8(x_vals, max_vals);
    }

    __m128i temp1, temp2, temp3, temp4;
    __m128i vals_r1, vals_r2, vals_r3, vals_r4;

    // Reduce min_vals to final min_val
    temp1 = _mm_srli_si128(min_vals, 8);
    vals_r1 = _mm_min_epu8(min_vals, temp1);
    temp2 = _mm_srli_si128(vals_r1, 4);
    vals_r2 = _mm_min_epu8(vals_r1, temp2);
    temp3 = _mm_srli_si128(vals_r2, 2);
    vals_r3 = _mm_min_epu8(vals_r2, temp3);
    temp4 = _mm_srli_si128(vals_r3, 1);
    vals_r4 = _mm_min_epu8(vals_r3, temp4);

    *x_min = (uint8_t)_mm_extract_epi8(vals_r4, 0);

    // Reduce max_vals to final max_val
    temp1 = _mm_srli_si128(max_vals, 8);
    vals_r1 = _mm_max_epu8(max_vals, temp1);
    temp2 = _mm_srli_si128(vals_r1, 4);
    vals_r2 = _mm_max_epu8(vals_r1, temp2);
    temp3 = _mm_srli_si128(vals_r2, 2);
    vals_r3 = _mm_max_epu8(vals_r2, temp3);
    temp4 = _mm_srli_si128(vals_r3, 1);
    vals_r4 = _mm_max_epu8(vals_r3, temp4);

    *x_max = (uint8_t)_mm_extract_epi8(vals_r4, 0);
    return true;
}
