//------------------------------------------------
//               Ch03_01_fcpp.cpp
//------------------------------------------------

#include <cstdint>
#include <immintrin.h>
#include "Ch03_01.h"

void PackedMathF32_Iavx(YmmVal c[8], const YmmVal* a, const YmmVal* b)
{
    __m256 a_vals = _mm256_load_ps((float*)a);
    __m256 b_vals = _mm256_load_ps((float*)b);
    const uint32_t abs_mask_val = 0x7FFFFFFF;
    __m256 abs_mask = _mm256_broadcast_ss((float*)&abs_mask_val);

    __m256 c_vals0 = _mm256_add_ps(a_vals, b_vals);
    __m256 c_vals1 = _mm256_sub_ps(a_vals, b_vals);
    __m256 c_vals2 = _mm256_mul_ps(a_vals, b_vals);
    __m256 c_vals3 = _mm256_div_ps(a_vals, b_vals);
    __m256 c_vals4 = _mm256_min_ps(a_vals, b_vals);
    __m256 c_vals5 = _mm256_max_ps(a_vals, b_vals);
    __m256 c_vals6 = _mm256_sqrt_ps(a_vals);
    __m256 c_vals7 = _mm256_and_ps(b_vals, abs_mask);

    _mm256_store_ps((float*)&c[0], c_vals0);
    _mm256_store_ps((float*)&c[1], c_vals1);
    _mm256_store_ps((float*)&c[2], c_vals2);
    _mm256_store_ps((float*)&c[3], c_vals3);
    _mm256_store_ps((float*)&c[4], c_vals4);
    _mm256_store_ps((float*)&c[5], c_vals5);
    _mm256_store_ps((float*)&c[6], c_vals6);
    _mm256_store_ps((float*)&c[7], c_vals7);
}

void PackedMathF64_Iavx(YmmVal c[8], const YmmVal* a, const YmmVal* b)
{
    __m256d a_vals = _mm256_load_pd((double*)a);
    __m256d b_vals = _mm256_load_pd((double*)b);
    const uint64_t abs_mask_val = 0x7FFFFFFFFFFFFFFF;
    __m256d abs_mask = _mm256_broadcast_sd((double*)&abs_mask_val);

    __m256d c_vals0 = _mm256_add_pd(a_vals, b_vals);
    __m256d c_vals1 = _mm256_sub_pd(a_vals, b_vals);
    __m256d c_vals2 = _mm256_mul_pd(a_vals, b_vals);
    __m256d c_vals3 = _mm256_div_pd(a_vals, b_vals);
    __m256d c_vals4 = _mm256_min_pd(a_vals, b_vals);
    __m256d c_vals5 = _mm256_max_pd(a_vals, b_vals);
    __m256d c_vals6 = _mm256_sqrt_pd(a_vals);
    __m256d c_vals7 = _mm256_and_pd(b_vals, abs_mask);

    _mm256_store_pd((double*)&c[0], c_vals0);
    _mm256_store_pd((double*)&c[1], c_vals1);
    _mm256_store_pd((double*)&c[2], c_vals2);
    _mm256_store_pd((double*)&c[3], c_vals3);
    _mm256_store_pd((double*)&c[4], c_vals4);
    _mm256_store_pd((double*)&c[5], c_vals5);
    _mm256_store_pd((double*)&c[6], c_vals6);
    _mm256_store_pd((double*)&c[7], c_vals7);
}
