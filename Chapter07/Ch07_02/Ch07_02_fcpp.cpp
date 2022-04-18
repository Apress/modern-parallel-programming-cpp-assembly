//------------------------------------------------
//               Ch07_02_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch07_02.h"

void MaskOpI64a_Iavx512(ZmmVal c[5], uint8_t mask, const ZmmVal* a, const ZmmVal* b)
{
    __m512i a_vals = _mm512_load_si512((__m512i*)a);
    __m512i b_vals = _mm512_load_si512((__m512i*)b);

    __m512i c_vals0 = _mm512_maskz_add_epi64(mask, a_vals, b_vals);
    __m512i c_vals1 = _mm512_maskz_sub_epi64(mask, a_vals, b_vals);
    __m512i c_vals2 = _mm512_maskz_mullo_epi64(mask, a_vals, b_vals);
    __m512i c_vals3 = _mm512_maskz_sllv_epi64(mask, a_vals, b_vals);
    __m512i c_vals4 = _mm512_maskz_srav_epi64(mask, a_vals, b_vals);

    _mm512_store_si512((__m512i*)&c[0], c_vals0);
    _mm512_store_si512((__m512i*)&c[1], c_vals1);
    _mm512_store_si512((__m512i*)&c[2], c_vals2);
    _mm512_store_si512((__m512i*)&c[3], c_vals3);
    _mm512_store_si512((__m512i*)&c[4], c_vals4);
}

void MaskOpI64b_Iavx512(ZmmVal c[5], uint8_t mask, const ZmmVal* a, const ZmmVal* b1, const ZmmVal* b2)
{
    __m512i a_vals = _mm512_load_si512((__m512i*)a);
    __m512i b1_vals = _mm512_load_si512((__m512i*)b1);
    __m512i b2_vals = _mm512_load_si512((__m512i*)b2);

    __m512i c_vals0 = _mm512_mask_add_epi64(a_vals, mask, b1_vals, b2_vals);
    __m512i c_vals1 = _mm512_mask_sub_epi64(a_vals, mask, b1_vals, b2_vals);
    __m512i c_vals2 = _mm512_mask_mullo_epi64(a_vals, mask, b1_vals, b2_vals);
    __m512i c_vals3 = _mm512_mask_sllv_epi64(a_vals, mask, b1_vals, b2_vals);
    __m512i c_vals4 = _mm512_mask_srav_epi64(a_vals, mask, b1_vals, b2_vals);

    _mm512_store_si512((__m512i*)&c[0], c_vals0);
    _mm512_store_si512((__m512i*)&c[1], c_vals1);
    _mm512_store_si512((__m512i*)&c[2], c_vals2);
    _mm512_store_si512((__m512i*)&c[3], c_vals3);
    _mm512_store_si512((__m512i*)&c[4], c_vals4);
}

void MaskOpI64c_Iavx512(ZmmVal* c, const ZmmVal* a, int64_t x1, int64_t x2)
{
    __m512i a_vals = _mm512_load_si512((__m512i*)a);
    __m512i x1_vals = _mm512_set1_epi64(x1);
    __m512i x2_vals = _mm512_set1_epi64(x2);

    // c_vals[i] = (a_vals[i] >= x1) ? a_vals[i] + x2 : a_vals[i]
    __mmask8 mask_ge = _mm512_cmpge_epi64_mask(a_vals, x1_vals);
    __m512i c_vals = _mm512_mask_add_epi64(a_vals, mask_ge, a_vals, x2_vals);

    _mm512_store_si512((__m512i*)c, c_vals);
}
