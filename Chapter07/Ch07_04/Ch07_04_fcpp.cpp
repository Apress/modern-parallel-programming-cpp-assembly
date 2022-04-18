//------------------------------------------------
//               Ch07_04_fcpp.cpp
//------------------------------------------------

#include <iostream>
#include <stdexcept>
#include <immintrin.h>
#include "Ch07_04.h"

void ComparePixels_Cpp(uint8_t* pb_des, const uint8_t* pb_src,
    size_t num_pixels, CmpOp cmp_op, uint8_t cmp_val)
{
    if (!CheckArgs(pb_des, pb_src, num_pixels))
        throw std::runtime_error("ComparePixels_Cpp() - CheckArgs failed");

    const uint8_t cmp_false = 0x00;
    const uint8_t cmp_true = 0xff;

    switch (cmp_op)
    {
        case CmpOp::EQ:
            for (size_t i = 0; i < num_pixels; i++)
                pb_des[i] = (pb_src[i] == cmp_val) ? cmp_true : cmp_false;
            break;

        case CmpOp::NE:
            for (size_t i = 0; i < num_pixels; i++)
                pb_des[i] = (pb_src[i] != cmp_val) ? cmp_true : cmp_false;
            break;

        case CmpOp::LT:
            for (size_t i = 0; i < num_pixels; i++)
                pb_des[i] = (pb_src[i] < cmp_val) ? cmp_true : cmp_false;
            break;

        case CmpOp::LE:
            for (size_t i = 0; i < num_pixels; i++)
                pb_des[i] = (pb_src[i] <= cmp_val) ? cmp_true : cmp_false;
            break;

        case CmpOp::GT:
            for (size_t i = 0; i < num_pixels; i++)
                pb_des[i] = (pb_src[i] > cmp_val) ? cmp_true : cmp_false;
            break;

        case CmpOp::GE:
            for (size_t i = 0; i < num_pixels; i++)
                pb_des[i] = (pb_src[i] >= cmp_val) ? cmp_true : cmp_false;
            break;

        default:
            throw std::runtime_error("ComparePixels_Cpp() - invalid cmp_op");
    }
}

void ComparePixels_Iavx512(uint8_t* pb_des, const uint8_t* pb_src, size_t num_pixels, CmpOp cmp_op, uint8_t cmp_val)
{
    if (!CheckArgs(pb_des, pb_src, num_pixels))
        throw std::runtime_error("ComparePixels_Iavx512() - CheckArgs failed");

    __m512i packed_255 = _mm512_set1_epi8((uint8_t)0xff);
    __m512i packed_cmp_val = _mm512_set1_epi8(cmp_val);

    __mmask64 cmp_mask;
    __m512i pixel_vals, mask_vals;
    const size_t num_simd_elements = 64;

    switch (cmp_op)
    {
        case CmpOp::EQ:
            for (size_t i = 0; i < num_pixels; i += num_simd_elements)
            {
                pixel_vals = _mm512_load_si512(&pb_src[i]);
                cmp_mask = _mm512_cmpeq_epu8_mask(pixel_vals, packed_cmp_val);
                mask_vals = _mm512_maskz_mov_epi8(cmp_mask, packed_255);
                _mm512_store_si512(&pb_des[i], mask_vals);
            }
            break;

        case CmpOp::NE:
            for (size_t i = 0; i < num_pixels; i += num_simd_elements)
            {
                pixel_vals = _mm512_load_si512(&pb_src[i]);
                cmp_mask = _mm512_cmpneq_epu8_mask(pixel_vals, packed_cmp_val);
                mask_vals = _mm512_maskz_mov_epi8(cmp_mask, packed_255);
                _mm512_store_si512(&pb_des[i], mask_vals);
            }
            break;

        case CmpOp::LT:
            for (size_t i = 0; i < num_pixels; i += num_simd_elements)
            {
                pixel_vals = _mm512_load_si512(&pb_src[i]);
                cmp_mask = _mm512_cmplt_epu8_mask(pixel_vals, packed_cmp_val);
                mask_vals = _mm512_maskz_mov_epi8(cmp_mask, packed_255);
                _mm512_store_si512(&pb_des[i], mask_vals);
            }
            break;

        case CmpOp::LE:
            for (size_t i = 0; i < num_pixels; i += num_simd_elements)
            {
                pixel_vals = _mm512_load_si512(&pb_src[i]);
                cmp_mask = _mm512_cmple_epu8_mask(pixel_vals, packed_cmp_val);
                mask_vals = _mm512_maskz_mov_epi8(cmp_mask, packed_255);
                _mm512_store_si512(&pb_des[i], mask_vals);
            }
            break;

        case CmpOp::GT:
            for (size_t i = 0; i < num_pixels; i += num_simd_elements)
            {
                pixel_vals = _mm512_load_si512(&pb_src[i]);
                cmp_mask = _mm512_cmpgt_epu8_mask(pixel_vals, packed_cmp_val);
                mask_vals = _mm512_maskz_mov_epi8(cmp_mask, packed_255);
                _mm512_store_si512(&pb_des[i], mask_vals);
            }
            break;

        case CmpOp::GE:
            for (size_t i = 0; i < num_pixels; i += num_simd_elements)
            {
                pixel_vals = _mm512_load_si512(&pb_src[i]);
                cmp_mask = _mm512_cmpge_epu8_mask(pixel_vals, packed_cmp_val);
                mask_vals = _mm512_maskz_mov_epi8(cmp_mask, packed_255);
                _mm512_store_si512(&pb_des[i], mask_vals);
            }
            break;

        default:
            throw std::runtime_error("ComparePixels_Iavx512() - invalid cmp_op");
    }
}
