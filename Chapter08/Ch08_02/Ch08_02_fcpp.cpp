//------------------------------------------------
//               Ch08_02_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch08_02.h"

void PackedCompareF32_Iavx512(uint16_t c[8], const ZmmVal* a, const ZmmVal* b)
{
    __m512 a_vals = _mm512_load_ps(a);
    __m512 b_vals = _mm512_load_ps(b);

    // Perform packed F32 compares
    c[0] = _mm512_cmp_ps_mask(a_vals, b_vals, _CMP_EQ_OQ);
    c[1] = _mm512_cmp_ps_mask(a_vals, b_vals, _CMP_NEQ_OQ);
    c[2] = _mm512_cmp_ps_mask(a_vals, b_vals, _CMP_LT_OQ);
    c[3] = _mm512_cmp_ps_mask(a_vals, b_vals, _CMP_LE_OQ);
    c[4] = _mm512_cmp_ps_mask(a_vals, b_vals, _CMP_GT_OQ);
    c[5] = _mm512_cmp_ps_mask(a_vals, b_vals, _CMP_GE_OQ);
    c[6] = _mm512_cmp_ps_mask(a_vals, b_vals, _CMP_ORD_Q);
    c[7] = _mm512_cmp_ps_mask(a_vals, b_vals, _CMP_UNORD_Q);
}

void PackedCompareF64_Iavx512(ZmmVal* c, const ZmmVal* a, const ZmmVal* b,
    double x1, double x2, double x3)
{
    __m512d a_vals = _mm512_load_pd(a);
    __m512d b_vals = _mm512_load_pd(b);
    __m512d x1_vals = _mm512_set1_pd(x1);
    __m512d x2_vals = _mm512_set1_pd(x2);
    __m512d x3_vals = _mm512_set1_pd(x3);

    __mmask8 m;
    m  = _mm512_cmp_pd_mask(a_vals, x1_vals, _CMP_GE_OQ);
    m &= _mm512_cmp_pd_mask(a_vals, x2_vals, _CMP_LE_OQ);
    m &= _mm512_cmp_pd_mask(b_vals, x1_vals, _CMP_GE_OQ);
    m &= _mm512_cmp_pd_mask(b_vals, x2_vals, _CMP_LE_OQ);

    __m512d temp0 = _mm512_mask_mul_pd(x3_vals, m, a_vals, b_vals);
    _mm512_store_pd(c, temp0);
}
