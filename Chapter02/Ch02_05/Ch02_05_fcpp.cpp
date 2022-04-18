//------------------------------------------------
//               Ch02_05_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch02_05.h"

void SllU16_Iavx(XmmVal* c, const XmmVal* a, int count)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_slli_epi16(a_vals, count);

    _mm_store_si128((__m128i*)c, b_vals);
}

void SrlU16_Iavx(XmmVal* c, const XmmVal* a, int count)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_srli_epi16(a_vals, count);

    _mm_store_si128((__m128i*)c, b_vals);
}

void SraU16_Iavx(XmmVal* c, const XmmVal* a, int count)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_srai_epi16(a_vals, count);

    _mm_store_si128((__m128i*)c, b_vals);
}
