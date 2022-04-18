//------------------------------------------------
//               Ch05_06_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <cstdint>
#include <immintrin.h>
#include "Ch05_06.h"
#include "MatrixF32.h"
#include "AlignedMem.h"

void MatVecMulF32_Cpp(Vec4x1_F32* vec_b, const MatrixF32& m,
    const Vec4x1_F32* vec_a, size_t num_vec)
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

void MatVecMulF32_Iavx2(Vec4x1_F32* vec_b, const MatrixF32& m,
    const Vec4x1_F32* vec_a, size_t num_vec)
{
    if (!CheckArgs(vec_b, m, vec_a, num_vec))
        throw std::runtime_error("MatVecMulF32_Iavx2() - CheckArgs failed");

    // Load matrix m
    const float* mm = m.Data();
    __m128 m_row0 = _mm_load_ps(&mm[0]);
    __m128 m_row1 = _mm_load_ps(&mm[4]);
    __m128 m_row2 = _mm_load_ps(&mm[8]);
    __m128 m_row3 = _mm_load_ps(&mm[12]);

    // Transpose m to get columns
    __m128 temp0 = _mm_unpacklo_ps(m_row0, m_row1);
    __m128 temp1 = _mm_unpackhi_ps(m_row0, m_row1);
    __m128 temp2 = _mm_unpacklo_ps(m_row2, m_row3);
    __m128 temp3 = _mm_unpackhi_ps(m_row2, m_row3);
    __m128 m_col0 = _mm_movelh_ps(temp0, temp2);
    __m128 m_col1 = _mm_movehl_ps(temp2, temp0);
    __m128 m_col2 = _mm_movelh_ps(temp1, temp3);
    __m128 m_col3 = _mm_movehl_ps(temp3, temp1);

    for (size_t i = 0; i < num_vec; i += 1)
    {
        // Broadcast components of next vec_a
        __m128 w_vals = _mm_broadcast_ss((float*)&vec_a[i].W);
        __m128 x_vals = _mm_broadcast_ss((float*)&vec_a[i].X);
        __m128 y_vals = _mm_broadcast_ss((float*)&vec_a[i].Y);
        __m128 z_vals = _mm_broadcast_ss((float*)&vec_a[i].Z);

        // Calculate and save matrix-vector product
        __m128 vec_b_vals = _mm_mul_ps(m_col0, w_vals);
        vec_b_vals = _mm_fmadd_ps(m_col1, x_vals, vec_b_vals);
        vec_b_vals = _mm_fmadd_ps(m_col2, y_vals, vec_b_vals);
        vec_b_vals = _mm_fmadd_ps(m_col3, z_vals, vec_b_vals);

        _mm_store_ps((float*)&vec_b[i], vec_b_vals);
    }
}
