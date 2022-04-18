//------------------------------------------------
//               Ch03_03_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <immintrin.h>
#include "Ch03_03.h"

void PackedConvertFP_Iavx(XmmVal* c, const XmmVal* a, CvtOp cvt_op)
{
    __m128 temp_ps;
    __m128i temp_si;
    __m128d temp_pd;

    switch (cvt_op)
    {
        case CvtOp::I32_TO_F32:
            temp_si = _mm_load_si128((__m128i*)a);
            temp_ps = _mm_cvtepi32_ps(temp_si);
            _mm_store_ps((float*)c, temp_ps);
            break;

        case CvtOp::F32_TO_I32:
            temp_ps = _mm_load_ps((float*)a);
            temp_si = _mm_cvtps_epi32(temp_ps);
            _mm_store_si128((__m128i*)c, temp_si);
            break;

        case CvtOp::I32_TO_F64:
            temp_si = _mm_load_si128((__m128i*)a);
            temp_pd = _mm_cvtepi32_pd(temp_si);
            _mm_store_pd((double*)c, temp_pd);
            break;

        case CvtOp::F64_TO_I32:
            temp_pd = _mm_load_pd((double*)a);
            temp_si = _mm_cvtpd_epi32(temp_pd);
            _mm_store_si128((__m128i*)c, temp_si);
            break;

        case CvtOp::F32_TO_F64:
            temp_ps = _mm_load_ps((float*)a);
            temp_pd = _mm_cvtps_pd(temp_ps);
            _mm_store_pd((double*)c, temp_pd);
            break;

        case CvtOp::F64_TO_F32:
            temp_pd = _mm_load_pd((double*)a);
            temp_ps = _mm_cvtpd_ps(temp_pd);
            _mm_store_ps((float*)c, temp_ps);
            break;
    
        default:
            throw std::runtime_error("Invalid value for cvt_op");
    }
}
