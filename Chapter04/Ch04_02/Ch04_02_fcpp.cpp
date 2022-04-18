//------------------------------------------------
//               Ch04_02_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch04_02.h"

void UnpackU32_U64_Iavx2(YmmVal c[2], const YmmVal* a, const YmmVal* b)
{
    __m256i a_vals = _mm256_load_si256((__m256i*)a);
    __m256i b_vals = _mm256_load_si256((__m256i*)b);

    __m256i c_vals0 = _mm256_unpacklo_epi32(a_vals, b_vals);
    __m256i c_vals1 = _mm256_unpackhi_epi32(a_vals, b_vals);

    _mm256_store_si256((__m256i*)&c[0], c_vals0);
    _mm256_store_si256((__m256i*)&c[1], c_vals1);
}

void PackI32_I16_Iavx2(YmmVal* c, const YmmVal* a, const YmmVal* b)
{
    __m256i a_vals = _mm256_load_si256((__m256i*)a);
    __m256i b_vals = _mm256_load_si256((__m256i*)b);

    __m256i c_vals = _mm256_packs_epi32(a_vals, b_vals);

    _mm256_store_si256((__m256i*)c, c_vals);
}
