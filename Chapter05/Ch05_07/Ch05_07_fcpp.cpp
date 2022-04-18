//------------------------------------------------
//               Ch05_07_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <cstdint>
#include <immintrin.h>
#include "Ch05_07.h"
#include "MatrixF64.h"
#include "AlignedMem.h"

void MatVecMulF64_Cpp(Vec4x1_F64* vec_b, MatrixF64& m,
    Vec4x1_F64* vec_a, size_t num_vec)
{
    if (!CheckArgs(vec_b, m, vec_a, num_vec))
        throw std::runtime_error("MatVecMulF64_Cpp() - CheckArgs failed");

    const double* mm = m.Data();

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

void MatVecMulF64_Iavx2(Vec4x1_F64* vec_b, MatrixF64& m,
    Vec4x1_F64* vec_a, size_t num_vec)
{
    if (!CheckArgs(vec_b, m, vec_a, num_vec))
        throw std::runtime_error("MatVecMulF64_Iavx2() - CheckArgs failed");

    // Load matrix m
    const double* mm = m.Data();
    __m256d m_row0 = _mm256_load_pd(&mm[0]);
    __m256d m_row1 = _mm256_load_pd(&mm[4]);
    __m256d m_row2 = _mm256_load_pd(&mm[8]);
    __m256d m_row3 = _mm256_load_pd(&mm[12]);

    // Transpose m to get columns
    __m256d temp0 = _mm256_unpacklo_pd(m_row0, m_row1);
    __m256d temp1 = _mm256_unpackhi_pd(m_row0, m_row1);
    __m256d temp2 = _mm256_unpacklo_pd(m_row2, m_row3);
    __m256d temp3 = _mm256_unpackhi_pd(m_row2, m_row3);
    __m256d m_col0 = _mm256_permute2f128_pd(temp0, temp2, 0x20);
    __m256d m_col1 = _mm256_permute2f128_pd(temp1, temp3, 0x20);
    __m256d m_col2 = _mm256_permute2f128_pd(temp0, temp2, 0x31);
    __m256d m_col3 = _mm256_permute2f128_pd(temp1, temp3, 0x31);

    for (size_t i = 0; i < num_vec; i += 1)
    {
        // Broadcast components of next vec_a
        __m256d w_vals = _mm256_broadcast_sd((double*)&vec_a[i].W);
        __m256d x_vals = _mm256_broadcast_sd((double*)&vec_a[i].X);
        __m256d y_vals = _mm256_broadcast_sd((double*)&vec_a[i].Y);
        __m256d z_vals = _mm256_broadcast_sd((double*)&vec_a[i].Z);

        // Calculate and save 2 matrix-vector products
        __m256d vec_b_vals = _mm256_mul_pd(m_col0, w_vals);
        vec_b_vals = _mm256_fmadd_pd(m_col1, x_vals, vec_b_vals);
        vec_b_vals = _mm256_fmadd_pd(m_col2, y_vals, vec_b_vals);
        vec_b_vals = _mm256_fmadd_pd(m_col3, z_vals, vec_b_vals);

        _mm256_store_pd((double*)&vec_b[i], vec_b_vals);
    }
}
