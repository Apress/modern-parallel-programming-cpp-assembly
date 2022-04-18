//------------------------------------------------
//               Ch02_03_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch02_03.h"

void MulI16_Iavx(XmmVal c[2], const XmmVal* a, const XmmVal* b)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_load_si128((__m128i*)b);

    __m128i temp_lo = _mm_mullo_epi16(a_vals, b_vals);
    __m128i temp_hi = _mm_mulhi_epi16(a_vals, b_vals);

    __m128i result_lo = _mm_unpacklo_epi16(temp_lo, temp_hi);
    __m128i result_hi = _mm_unpackhi_epi16(temp_lo, temp_hi);

    _mm_store_si128((__m128i*)&c[0], result_lo);
    _mm_store_si128((__m128i*)&c[1], result_hi);
}

void MulI32a_Iavx(XmmVal* c, const XmmVal* a, const XmmVal* b)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_load_si128((__m128i*)b);
    __m128i c_vals = _mm_mullo_epi32(a_vals, b_vals);

    _mm_store_si128((__m128i*)c, c_vals);
}

void MulI32b_Iavx(XmmVal c[2], const XmmVal* a, const XmmVal* b)
{
    __m128i a_vals = _mm_load_si128((__m128i*)a);
    __m128i b_vals = _mm_load_si128((__m128i*)b);

    __m128i temp1 = _mm_mul_epi32(a_vals, b_vals);      // q2 | q0
    __m128i temp2 = _mm_srli_si128(a_vals, 4);
    __m128i temp3 = _mm_srli_si128(b_vals, 4);
    __m128i temp4 = _mm_mul_epi32(temp2, temp3);        // q3 | q1

    *(&c[0].m_I64[0]) = _mm_extract_epi64(temp1, 0);    // q0
    *(&c[0].m_I64[1]) = _mm_extract_epi64(temp4, 0);    // q1
    *(&c[1].m_I64[0]) = _mm_extract_epi64(temp1, 1);    // q2
    *(&c[1].m_I64[1]) = _mm_extract_epi64(temp4, 1);    // q3
}
