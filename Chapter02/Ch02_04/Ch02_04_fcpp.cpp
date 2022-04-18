//------------------------------------------------
//               Ch02_04_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch02_04.h"

void AndU16_Iavx(XmmVal* c, const XmmVal* a, const XmmVal* b)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_load_si128((__m128i*)b);
    __m128i c_vals = _mm_and_si128(a_vals, b_vals);

    _mm_store_si128((__m128i*)c, c_vals);
}

void OrU16_Iavx(XmmVal* c, const XmmVal* a, const XmmVal* b)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_load_si128((__m128i*)b);
    __m128i c_vals = _mm_or_si128(a_vals, b_vals);

    _mm_store_si128((__m128i*)c, c_vals);
}

void XorU16_Iavx(XmmVal* c, const XmmVal* a, const XmmVal* b)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_load_si128((__m128i*)b);
    __m128i c_vals = _mm_xor_si128(a_vals, b_vals);

    _mm_store_si128((__m128i*)c, c_vals);
}
