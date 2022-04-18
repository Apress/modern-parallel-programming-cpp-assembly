//------------------------------------------------
//               Ch07_01_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch07_01.h"

void MathI16_Iavx512(ZmmVal c[6], const ZmmVal* a, const ZmmVal* b)
{
    __m512i a_vals = _mm512_load_si512((__m512i*)a);
    __m512i b_vals = _mm512_load_si512((__m512i*)b);

    __m512i c_vals0 = _mm512_add_epi16(a_vals, b_vals);
    __m512i c_vals1 = _mm512_adds_epi16(a_vals, b_vals);
    __m512i c_vals2 = _mm512_sub_epi16(a_vals, b_vals);
    __m512i c_vals3 = _mm512_subs_epi16(a_vals, b_vals);
    __m512i c_vals4 = _mm512_min_epi16(a_vals, b_vals);
    __m512i c_vals5 = _mm512_max_epi16(a_vals, b_vals);

    _mm512_store_si512((__m512i*)&c[0], c_vals0);
    _mm512_store_si512((__m512i*)&c[1], c_vals1);
    _mm512_store_si512((__m512i*)&c[2], c_vals2);
    _mm512_store_si512((__m512i*)&c[3], c_vals3);
    _mm512_store_si512((__m512i*)&c[4], c_vals4);
    _mm512_store_si512((__m512i*)&c[5], c_vals5);
}

void MathI64_Iavx512(ZmmVal c[6], const ZmmVal* a, const ZmmVal* b)
{
    __m512i a_vals = _mm512_load_si512((__m512i*)a);
    __m512i b_vals = _mm512_load_si512((__m512i*)b);

    __m512i c_vals0 = _mm512_add_epi64(a_vals, b_vals);
    __m512i c_vals1 = _mm512_sub_epi64(a_vals, b_vals);
    __m512i c_vals2 = _mm512_mullo_epi64(a_vals, b_vals);
    __m512i c_vals3 = _mm512_sllv_epi64(a_vals, b_vals);
    __m512i c_vals4 = _mm512_srav_epi64(a_vals, b_vals);
    __m512i c_vals5 = _mm512_abs_epi64(a_vals);

    _mm512_store_si512((__m512i*)&c[0], c_vals0);
    _mm512_store_si512((__m512i*)&c[1], c_vals1);
    _mm512_store_si512((__m512i*)&c[2], c_vals2);
    _mm512_store_si512((__m512i*)&c[3], c_vals3);
    _mm512_store_si512((__m512i*)&c[4], c_vals4);
    _mm512_store_si512((__m512i*)&c[5], c_vals5);
}
