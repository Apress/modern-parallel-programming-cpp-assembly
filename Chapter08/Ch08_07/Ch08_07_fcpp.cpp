//------------------------------------------------
//               Ch08_07_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <cstdint>
#include <immintrin.h>
#include "Ch08_07.h"
#include "MatrixF32.h"
#include "AlignedMem.h"

// Permutation indices for matrix columns
alignas(64) const uint32_t c_MatIndCol0[] { 0, 4, 8, 12, 0, 4, 8, 12,
                                            0, 4, 8, 12, 0, 4, 8, 12 };
alignas(64) const uint32_t c_MatIndCol1[] { 1, 5, 9, 13, 1, 5, 9, 13,
                                            1, 5, 9, 13, 1, 5, 9, 13 };
alignas(64) const uint32_t c_MatIndCol2[] { 2, 6, 10, 14, 2, 6, 10, 14,
                                            2, 6, 10, 14, 2, 6, 10, 14 };
alignas(64) const uint32_t c_MatIndCol3[] { 3, 7, 11, 15, 3, 7, 11, 15,
                                            3, 7, 11, 15, 3, 7, 11, 15 };

// Permutation indices for vector components
alignas(64) const uint32_t c_VecIndW[] { 0, 0, 0, 0, 4, 4, 4, 4,
                                         8, 8, 8, 8, 12, 12, 12, 12 };
alignas(64) const uint32_t c_VecIndX[] { 1, 1, 1, 1, 5, 5, 5, 5,
                                         9, 9, 9, 9, 13, 13, 13, 13 };
alignas(64) const uint32_t c_VecIndY[] { 2, 2, 2, 2, 6, 6, 6, 6,
                                         10, 10, 10, 10, 14, 14, 14, 14 };
alignas(64) const uint32_t c_VecIndZ[] { 3, 3, 3, 3, 7, 7, 7, 7,
                                         11, 11, 11, 11, 15, 15, 15, 15 };

void MatVecMulF32_Cpp(Vec4x1_F32* vec_b, MatrixF32& m, Vec4x1_F32* vec_a,
    size_t num_vec)
{
    if (!CheckArgs(vec_b, m, vec_a, num_vec))
        throw std::runtime_error("MatVecMulF32_Cpp() - CheckArgs failed");

    const float* mm = m.Data();

    // Calculate matrix-vector products
    for (size_t i = 0; i < num_vec; i++)
    {
        vec_b[i].W =  mm[0] * vec_a[i].W + mm[1] * vec_a[i].X;
        vec_b[i].W += mm[2] * vec_a[i].Y + mm[3] * vec_a[i].Z;

        vec_b[i].X =  mm[4] * vec_a[i].W + mm[5] * vec_a[i].X;
        vec_b[i].X += mm[6] * vec_a[i].Y + mm[7] * vec_a[i].Z;

        vec_b[i].Y =  mm[8] * vec_a[i].W + mm[9] * vec_a[i].X;
        vec_b[i].Y += mm[10] * vec_a[i].Y + mm[11] * vec_a[i].Z;

        vec_b[i].Z =  mm[12] * vec_a[i].W + mm[13] * vec_a[i].X;
        vec_b[i].Z += mm[14] * vec_a[i].Y + mm[15] * vec_a[i].Z;
    }
}

void MatVecMulF32a_Iavx512(Vec4x1_F32* vec_b, MatrixF32& m, Vec4x1_F32* vec_a,
    size_t num_vec)
{
    if (!CheckArgs(vec_b, m, vec_a, num_vec))
        throw std::runtime_error("MatVecMulF32a_Iavx512() - CheckArgs failed");

    // Load indices for matrix and vector permutations
    __m512i m_ind_col0 = _mm512_load_epi32(c_MatIndCol0);
    __m512i m_ind_col1 = _mm512_load_epi32(c_MatIndCol1);
    __m512i m_ind_col2 = _mm512_load_epi32(c_MatIndCol2);
    __m512i m_ind_col3 = _mm512_load_epi32(c_MatIndCol3);

    __m512i v_ind_w = _mm512_load_epi32(c_VecIndW);
    __m512i v_ind_x = _mm512_load_epi32(c_VecIndX);
    __m512i v_ind_y = _mm512_load_epi32(c_VecIndY);
    __m512i v_ind_z = _mm512_load_epi32(c_VecIndZ);

    // Load source matrix and permute 4 copies of each column
    __m512 m_vals = _mm512_load_ps(m.Data());
    __m512 m_col0_vals = _mm512_permutexvar_ps(m_ind_col0, m_vals);
    __m512 m_col1_vals = _mm512_permutexvar_ps(m_ind_col1, m_vals);
    __m512 m_col2_vals = _mm512_permutexvar_ps(m_ind_col2, m_vals);
    __m512 m_col3_vals = _mm512_permutexvar_ps(m_ind_col3, m_vals);

    // Calculate matrix-vector products
    size_t i = 0;
    const size_t num_vec_per_iteration = 4;

    for (; num_vec - i >= num_vec_per_iteration; i += num_vec_per_iteration)
    {
        // Load next block of 4 vectors
        __m512 va_vals = _mm512_load_ps(&vec_a[i]);

        // Permute vectors into W, X, Y, Z components
        __m512 va_w_vals = _mm512_permutexvar_ps(v_ind_w, va_vals);
        __m512 va_x_vals = _mm512_permutexvar_ps(v_ind_x, va_vals);
        __m512 va_y_vals = _mm512_permutexvar_ps(v_ind_y, va_vals);
        __m512 va_z_vals = _mm512_permutexvar_ps(v_ind_z, va_vals);

        // Calculate and save matrix-vector products
        __m512 vb_vals = _mm512_mul_ps(m_col0_vals, va_w_vals);
        vb_vals = _mm512_fmadd_ps(m_col1_vals, va_x_vals, vb_vals);
        vb_vals = _mm512_fmadd_ps(m_col2_vals, va_y_vals, vb_vals);
        vb_vals = _mm512_fmadd_ps(m_col3_vals, va_z_vals, vb_vals);

        _mm512_store_ps(&vec_b[i], vb_vals);
    }

    if (i < num_vec)
    {
        __m128 m_col0_vals2 = _mm512_extractf32x4_ps(m_col0_vals, 0);
        __m128 m_col1_vals2 = _mm512_extractf32x4_ps(m_col1_vals, 1);
        __m128 m_col2_vals2 = _mm512_extractf32x4_ps(m_col2_vals, 2);
        __m128 m_col3_vals2 = _mm512_extractf32x4_ps(m_col3_vals, 3);

        for (; i < num_vec; i++)
        {
            __m128 va_w_vals = _mm_broadcast_ss(&vec_a[i].W);
            __m128 va_x_vals = _mm_broadcast_ss(&vec_a[i].X);
            __m128 va_y_vals = _mm_broadcast_ss(&vec_a[i].Y);
            __m128 va_z_vals = _mm_broadcast_ss(&vec_a[i].Z);

            __m128 vb_vals = _mm_mul_ps(m_col0_vals2, va_w_vals);
            vb_vals = _mm_fmadd_ps(m_col1_vals2, va_x_vals, vb_vals);
            vb_vals = _mm_fmadd_ps(m_col2_vals2, va_y_vals, vb_vals);
            vb_vals = _mm_fmadd_ps(m_col3_vals2, va_z_vals, vb_vals);

            _mm_store_ps((float*)&vec_b[i], vb_vals);
        }
    }
}

void MatVecMulF32b_Iavx512(Vec4x1_F32* vec_b, MatrixF32& m, Vec4x1_F32* vec_a,
    size_t num_vec)
{
    if (!CheckArgs(vec_b, m, vec_a, num_vec))
        throw std::runtime_error("MatVecMulF32b_Iavx512() - CheckArgs failed");

    // Load indices for matrix and vector permutations
    __m512i m_ind_col0 = _mm512_load_epi32(c_MatIndCol0);
    __m512i m_ind_col1 = _mm512_load_epi32(c_MatIndCol1);
    __m512i m_ind_col2 = _mm512_load_epi32(c_MatIndCol2);
    __m512i m_ind_col3 = _mm512_load_epi32(c_MatIndCol3);

    __m512i v_ind_w = _mm512_load_epi32(c_VecIndW);
    __m512i v_ind_x = _mm512_load_epi32(c_VecIndX);
    __m512i v_ind_y = _mm512_load_epi32(c_VecIndY);
    __m512i v_ind_z = _mm512_load_epi32(c_VecIndZ);

    // Load source matrix and permute 4 copies of each column
    __m512 m_vals = _mm512_load_ps(m.Data());
    __m512 m_col0_vals = _mm512_permutexvar_ps(m_ind_col0, m_vals);
    __m512 m_col1_vals = _mm512_permutexvar_ps(m_ind_col1, m_vals);
    __m512 m_col2_vals = _mm512_permutexvar_ps(m_ind_col2, m_vals);
    __m512 m_col3_vals = _mm512_permutexvar_ps(m_ind_col3, m_vals);

    // Calculate matrix-vector products
    size_t i = 0;
    const size_t num_vec_per_iteration = 4;

    for (; num_vec - i >= num_vec_per_iteration; i += num_vec_per_iteration)
    {
        // Load next block of 4 vectors
        __m512 va_vals = _mm512_load_ps(&vec_a[i]);

        // Permute vectors into W, X, Y, Z components
        __m512 va_w_vals = _mm512_permutexvar_ps(v_ind_w, va_vals);
        __m512 va_x_vals = _mm512_permutexvar_ps(v_ind_x, va_vals);
        __m512 va_y_vals = _mm512_permutexvar_ps(v_ind_y, va_vals);
        __m512 va_z_vals = _mm512_permutexvar_ps(v_ind_z, va_vals);

        // Calculate and save matrix-vector products
        __m512 vb_vals = _mm512_mul_ps(m_col0_vals, va_w_vals);
        vb_vals = _mm512_fmadd_ps(m_col1_vals, va_x_vals, vb_vals);
        vb_vals = _mm512_fmadd_ps(m_col2_vals, va_y_vals, vb_vals);
        vb_vals = _mm512_fmadd_ps(m_col3_vals, va_z_vals, vb_vals);

#if defined(__GNUG__)
        _mm512_stream_ps((float*)&vec_b[i], vb_vals);
#else
        _mm512_stream_ps(&vec_b[i], vb_vals);
#endif
    }

    if (i < num_vec)
    {
        __m128 m_col0_vals2 = _mm512_extractf32x4_ps(m_col0_vals, 0);
        __m128 m_col1_vals2 = _mm512_extractf32x4_ps(m_col1_vals, 1);
        __m128 m_col2_vals2 = _mm512_extractf32x4_ps(m_col2_vals, 2);
        __m128 m_col3_vals2 = _mm512_extractf32x4_ps(m_col3_vals, 3);

        for (; i < num_vec; i++)
        {
            __m128 va_w_vals = _mm_broadcast_ss(&vec_a[i].W);
            __m128 va_x_vals = _mm_broadcast_ss(&vec_a[i].X);
            __m128 va_y_vals = _mm_broadcast_ss(&vec_a[i].Y);
            __m128 va_z_vals = _mm_broadcast_ss(&vec_a[i].Z);

            __m128 vb_vals = _mm_mul_ps(m_col0_vals2, va_w_vals);
            vb_vals = _mm_fmadd_ps(m_col1_vals2, va_x_vals, vb_vals);
            vb_vals = _mm_fmadd_ps(m_col2_vals2, va_y_vals, vb_vals);
            vb_vals = _mm_fmadd_ps(m_col3_vals2, va_z_vals, vb_vals);

            _mm_stream_ps((float*)&vec_b[i], vb_vals);
        }
    }
}
