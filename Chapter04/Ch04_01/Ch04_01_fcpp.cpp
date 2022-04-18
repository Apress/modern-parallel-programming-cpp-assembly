//------------------------------------------------
//               Ch04_01_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch04_01.h"

void MathI16_Iavx2(YmmVal c[6], const YmmVal* a, const YmmVal* b)
{
    __m256i a_vals = _mm256_load_si256((__m256i*)a);
    __m256i b_vals = _mm256_load_si256((__m256i*)b);

    __m256i c_vals0 = _mm256_add_epi16(a_vals, b_vals);
    __m256i c_vals1 = _mm256_adds_epi16(a_vals, b_vals);
    __m256i c_vals2 = _mm256_sub_epi16(a_vals, b_vals);
    __m256i c_vals3 = _mm256_subs_epi16(a_vals, b_vals);
    __m256i c_vals4 = _mm256_min_epi16(a_vals, b_vals); 
    __m256i c_vals5 = _mm256_max_epi16(a_vals, b_vals); 

    _mm256_store_si256((__m256i*)&c[0], c_vals0);
    _mm256_store_si256((__m256i*)&c[1], c_vals1);
    _mm256_store_si256((__m256i*)&c[2], c_vals2);
    _mm256_store_si256((__m256i*)&c[3], c_vals3);
    _mm256_store_si256((__m256i*)&c[4], c_vals4);
    _mm256_store_si256((__m256i*)&c[5], c_vals5);
}

void MathI32_Iavx2(YmmVal c[6], const YmmVal* a, const YmmVal* b)
{
    __m256i a_vals = _mm256_load_si256((__m256i*)a);
    __m256i b_vals = _mm256_load_si256((__m256i*)b);

    __m256i c_vals0 = _mm256_add_epi32(a_vals, b_vals);
    __m256i c_vals1 = _mm256_sub_epi32(a_vals, b_vals);
    __m256i c_vals2 = _mm256_mullo_epi32(a_vals, b_vals);
    __m256i c_vals3 = _mm256_sllv_epi32(a_vals, b_vals);
    __m256i c_vals4 = _mm256_srav_epi32(a_vals, b_vals);
    __m256i c_vals5 = _mm256_abs_epi32(a_vals);

    _mm256_store_si256((__m256i*)&c[0], c_vals0);
    _mm256_store_si256((__m256i*)&c[1], c_vals1);
    _mm256_store_si256((__m256i*)&c[2], c_vals2);
    _mm256_store_si256((__m256i*)&c[3], c_vals3);
    _mm256_store_si256((__m256i*)&c[4], c_vals4);
    _mm256_store_si256((__m256i*)&c[5], c_vals5);
}
