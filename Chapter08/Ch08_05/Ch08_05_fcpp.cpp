//------------------------------------------------
//               Ch08_05_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <immintrin.h>
#include "Ch08_05.h"

void MatrixMulF32_Cpp(MatrixF32& c, const MatrixF32& a, const MatrixF32& b)
{
    MatrixF32::Mul(c, a, b);
}

void MatrixMulF32_Iavx512(MatrixF32& c, const MatrixF32& a, const MatrixF32& b)
{
    if (!CheckArgs(c, a, b))
        throw std::runtime_error("MatrixMulF32_Iavx512() CheckArgs failed");

    const float* aa = a.Data();
    const float* bb = b.Data();
    float* cc = c.Data();

    size_t c_nrows = c.GetNumRows();
    size_t c_ncols = c.GetNumCols();
    size_t a_ncols = a.GetNumCols();
    size_t b_ncols = b.GetNumCols();
    size_t m = a_ncols;

    const size_t num_simd_elements = 16;
    size_t num_residual_cols = c_ncols % num_simd_elements;

    // res_mask = 2 ** num_residual_cols - 1
    __mmask16 res_mask = (__mmask16)((1 << num_residual_cols) - 1);

    for (size_t i = 0; i < c_nrows; i++)
    {
        size_t j = 0;

        while (j + num_simd_elements <= c_ncols)
        {
            __m512 c_vals = _mm512_setzero_ps();

            for (size_t k = 0; k < m; k++)
            {
                __m512 a_vals = _mm512_set1_ps(aa[i * a_ncols + k]);
                __m512 b_vals = _mm512_loadu_ps(&bb[k * b_ncols + j]);
                
                c_vals = _mm512_fmadd_ps(a_vals, b_vals, c_vals);
            }

            _mm512_storeu_ps(&cc[i * c_ncols + j], c_vals);
            j += num_simd_elements;
        }

        if (num_residual_cols != 0)
        {
            __m512 c_vals = _mm512_setzero_ps();

            for (size_t k = 0; k < m; k++)
            {
                __m512 a_vals = _mm512_set1_ps(aa[i * a_ncols + k]);
                __m512 b_vals = _mm512_maskz_loadu_ps(res_mask, &bb[k * b_ncols + j]);
                
                c_vals = _mm512_fmadd_ps(a_vals, b_vals, c_vals);
            }

            _mm512_mask_storeu_ps(&cc[i * c_ncols + j], res_mask, c_vals);
        }
    }
}
