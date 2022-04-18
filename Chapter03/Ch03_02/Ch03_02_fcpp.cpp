//------------------------------------------------
//               Ch03_02_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch03_02.h"

void PackedCompareF32_Iavx(YmmVal c[8], const YmmVal* a, const YmmVal* b)
{
    __m256 a_vals = _mm256_load_ps((float*)a);
    __m256 b_vals = _mm256_load_ps((float*)b);

    __m256 c_vals0 = _mm256_cmp_ps(a_vals, b_vals, _CMP_EQ_OQ);
    __m256 c_vals1 = _mm256_cmp_ps(a_vals, b_vals, _CMP_NEQ_OQ);
    __m256 c_vals2 = _mm256_cmp_ps(a_vals, b_vals, _CMP_LT_OQ);
    __m256 c_vals3 = _mm256_cmp_ps(a_vals, b_vals, _CMP_LE_OQ);
    __m256 c_vals4 = _mm256_cmp_ps(a_vals, b_vals, _CMP_GT_OQ);
    __m256 c_vals5 = _mm256_cmp_ps(a_vals, b_vals, _CMP_GE_OQ);
    __m256 c_vals6 = _mm256_cmp_ps(a_vals, b_vals, _CMP_ORD_Q);
    __m256 c_vals7 = _mm256_cmp_ps(a_vals, b_vals, _CMP_UNORD_Q);

    _mm256_store_ps((float*)&c[0], c_vals0);
    _mm256_store_ps((float*)&c[1], c_vals1);
    _mm256_store_ps((float*)&c[2], c_vals2);
    _mm256_store_ps((float*)&c[3], c_vals3);
    _mm256_store_ps((float*)&c[4], c_vals4);
    _mm256_store_ps((float*)&c[5], c_vals5);
    _mm256_store_ps((float*)&c[6], c_vals6);
    _mm256_store_ps((float*)&c[7], c_vals7);
}

void PackedCompareF64_Iavx(YmmVal c[8], const YmmVal* a, const YmmVal* b)
{
    __m256d a_vals = _mm256_load_pd((double*)a);
    __m256d b_vals = _mm256_load_pd((double*)b);

    __m256d c_vals0 = _mm256_cmp_pd(a_vals, b_vals, _CMP_EQ_OQ);
    __m256d c_vals1 = _mm256_cmp_pd(a_vals, b_vals, _CMP_NEQ_OQ);
    __m256d c_vals2 = _mm256_cmp_pd(a_vals, b_vals, _CMP_LT_OQ);
    __m256d c_vals3 = _mm256_cmp_pd(a_vals, b_vals, _CMP_LE_OQ);
    __m256d c_vals4 = _mm256_cmp_pd(a_vals, b_vals, _CMP_GT_OQ);
    __m256d c_vals5 = _mm256_cmp_pd(a_vals, b_vals, _CMP_GE_OQ);
    __m256d c_vals6 = _mm256_cmp_pd(a_vals, b_vals, _CMP_ORD_Q);
    __m256d c_vals7 = _mm256_cmp_pd(a_vals, b_vals, _CMP_UNORD_Q);

    _mm256_store_pd((double*)&c[0], c_vals0);
    _mm256_store_pd((double*)&c[1], c_vals1);
    _mm256_store_pd((double*)&c[2], c_vals2);
    _mm256_store_pd((double*)&c[3], c_vals3);
    _mm256_store_pd((double*)&c[4], c_vals4);
    _mm256_store_pd((double*)&c[5], c_vals5);
    _mm256_store_pd((double*)&c[6], c_vals6);
    _mm256_store_pd((double*)&c[7], c_vals7);
}
