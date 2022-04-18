//------------------------------------------------
//               Ch02_02_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch02_02.h"

extern void SubI32_Iavx(XmmVal* c, const XmmVal* a, const XmmVal* b)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_load_si128((__m128i*)b);
    __m128i c_vals = _mm_sub_epi32(a_vals, b_vals);

    _mm_store_si128((__m128i*)c, c_vals);
}

extern void SubI64_Iavx(XmmVal* c, const XmmVal* a, const XmmVal* b)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_load_si128((__m128i*)b);
    __m128i c_vals = _mm_sub_epi64(a_vals, b_vals);

    _mm_store_si128((__m128i*)c, c_vals);
}
