//------------------------------------------------
//               Ch08_01_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch08_01.h"

void PackedMathF32_Iavx512(ZmmVal c[8], const ZmmVal* a, const ZmmVal* b)
{
    __m512 a_vals = _mm512_load_ps(a);
    __m512 b_vals = _mm512_load_ps(b);

    __m512 c_vals0 = _mm512_add_ps(a_vals, b_vals);
    __m512 c_vals1 = _mm512_sub_ps(a_vals, b_vals);
    __m512 c_vals2 = _mm512_mul_ps(a_vals, b_vals);
    __m512 c_vals3 = _mm512_div_ps(a_vals, b_vals);
    __m512 c_vals4 = _mm512_min_ps(a_vals, b_vals);
    __m512 c_vals5 = _mm512_max_ps(a_vals, b_vals);
    __m512 c_vals6 = _mm512_sqrt_ps(a_vals);
    __m512 c_vals7 = _mm512_abs_ps(b_vals);

    _mm512_store_ps(&c[0], c_vals0);
    _mm512_store_ps(&c[1], c_vals1);
    _mm512_store_ps(&c[2], c_vals2);
    _mm512_store_ps(&c[3], c_vals3);
    _mm512_store_ps(&c[4], c_vals4);
    _mm512_store_ps(&c[5], c_vals5);
    _mm512_store_ps(&c[6], c_vals6);
    _mm512_store_ps(&c[7], c_vals7);
}

void PackedMathF64_Iavx512(ZmmVal c[8], const ZmmVal* a, const ZmmVal* b)
{
    __m512d a_vals = _mm512_load_pd(a);
    __m512d b_vals = _mm512_load_pd(b);

    __m512d c_vals0 = _mm512_add_pd(a_vals, b_vals);
    __m512d c_vals1 = _mm512_sub_pd(a_vals, b_vals);
    __m512d c_vals2 = _mm512_mul_pd(a_vals, b_vals);
    __m512d c_vals3 = _mm512_div_pd(a_vals, b_vals);
    __m512d c_vals4 = _mm512_min_pd(a_vals, b_vals);
    __m512d c_vals5 = _mm512_max_pd(a_vals, b_vals);
    __m512d c_vals6 = _mm512_sqrt_pd(a_vals);
    __m512d c_vals7 = _mm512_abs_pd(b_vals);

    _mm512_store_pd(&c[0], c_vals0);
    _mm512_store_pd(&c[1], c_vals1);
    _mm512_store_pd(&c[2], c_vals2);
    _mm512_store_pd(&c[3], c_vals3);
    _mm512_store_pd(&c[4], c_vals4);
    _mm512_store_pd(&c[5], c_vals5);
    _mm512_store_pd(&c[6], c_vals6);
    _mm512_store_pd(&c[7], c_vals7);
}
