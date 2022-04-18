//------------------------------------------------
//               Ch04_03_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch04_03.h"

void ZeroExtU8_U16_Iavx2(YmmVal c[2], YmmVal* a)
{
    __m128i a_vals_u8_lo = _mm_load_si128((__m128i*)&a->m_U8[0]);
    __m128i a_vals_u8_hi = _mm_load_si128((__m128i*)&a->m_U8[16]);

    __m256i c_vals_u16_lo = _mm256_cvtepu8_epi16(a_vals_u8_lo);
    __m256i c_vals_u16_hi = _mm256_cvtepu8_epi16(a_vals_u8_hi);

    _mm256_store_si256((__m256i*)&c[0], c_vals_u16_lo);
    _mm256_store_si256((__m256i*)&c[1], c_vals_u16_hi);
}

void ZeroExtU8_U32_Iavx2(YmmVal c[4], YmmVal* a)
{
    __m128i a_vals_u8_0 = _mm_loadl_epi64((__m128i*)&a->m_U8[0]);
    __m128i a_vals_u8_1 = _mm_loadl_epi64((__m128i*)&a->m_U8[8]);
    __m128i a_vals_u8_2 = _mm_loadl_epi64((__m128i*)&a->m_U8[16]);
    __m128i a_vals_u8_3 = _mm_loadl_epi64((__m128i*)&a->m_U8[24]);

    __m256i c_vals_u32_0 = _mm256_cvtepu8_epi32(a_vals_u8_0);
    __m256i c_vals_u32_1 = _mm256_cvtepu8_epi32(a_vals_u8_1);
    __m256i c_vals_u32_2 = _mm256_cvtepu8_epi32(a_vals_u8_2);
    __m256i c_vals_u32_3 = _mm256_cvtepu8_epi32(a_vals_u8_3);

    _mm256_store_si256((__m256i*)&c[0], c_vals_u32_0);
    _mm256_store_si256((__m256i*)&c[1], c_vals_u32_1);
    _mm256_store_si256((__m256i*)&c[2], c_vals_u32_2);
    _mm256_store_si256((__m256i*)&c[3], c_vals_u32_3);
}

void SignExtI16_I32_Iavx2(YmmVal c[2], YmmVal* a)
{
    __m128i a_vals_i16_lo = _mm_load_si128((__m128i*)&a->m_I16[0]);
    __m128i a_vals_i16_hi = _mm_load_si128((__m128i*)&a->m_I16[8]);

    __m256i c_vals_i32_lo = _mm256_cvtepi16_epi32(a_vals_i16_lo);
    __m256i c_vals_i32_hi = _mm256_cvtepi16_epi32(a_vals_i16_hi);

    _mm256_store_si256((__m256i*)&c[0], c_vals_i32_lo);
    _mm256_store_si256((__m256i*)&c[1], c_vals_i32_hi);
}

void SignExtI16_I64_Iavx2(YmmVal c[4], YmmVal* a)
{
    __m128i a_vals_i16_0 = _mm_loadl_epi64((__m128i*)&a->m_I16[0]);
    __m128i a_vals_i16_1 = _mm_loadl_epi64((__m128i*)&a->m_I16[4]);
    __m128i a_vals_i16_2 = _mm_loadl_epi64((__m128i*)&a->m_I16[8]);
    __m128i a_vals_i16_3 = _mm_loadl_epi64((__m128i*)&a->m_I16[12]);

    __m256i c_vals_i64_0 = _mm256_cvtepi16_epi64(a_vals_i16_0);
    __m256i c_vals_i64_1 = _mm256_cvtepi16_epi64(a_vals_i16_1);
    __m256i c_vals_i64_2 = _mm256_cvtepi16_epi64(a_vals_i16_2);
    __m256i c_vals_i64_3 = _mm256_cvtepi16_epi64(a_vals_i16_3);

    _mm256_store_si256((__m256i*)&c[0], c_vals_i64_0);
    _mm256_store_si256((__m256i*)&c[1], c_vals_i64_1);
    _mm256_store_si256((__m256i*)&c[2], c_vals_i64_2);
    _mm256_store_si256((__m256i*)&c[3], c_vals_i64_3);
}
