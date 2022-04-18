//------------------------------------------------
//               Ch02_01_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch02_01.h"

void AddI16_Iavx(XmmVal* c1, XmmVal* c2, const XmmVal* a, const XmmVal* b)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_load_si128((__m128i*)b);

    __m128i c1_vals = _mm_add_epi16(a_vals, b_vals);
    __m128i c2_vals = _mm_adds_epi16(a_vals, b_vals);

    _mm_store_si128((__m128i*)c1, c1_vals);
    _mm_store_si128((__m128i*)c2, c2_vals);
}

void AddU16_Iavx(XmmVal* c1, XmmVal* c2, const XmmVal* a, const XmmVal* b)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_load_si128((__m128i*)b);

    __m128i c1_vals = _mm_add_epi16(a_vals, b_vals);
    __m128i c2_vals = _mm_adds_epu16(a_vals, b_vals);

    _mm_store_si128((__m128i*)c1, c1_vals);
    _mm_store_si128((__m128i*)c2, c2_vals);
}
