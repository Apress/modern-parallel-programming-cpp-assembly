//------------------------------------------------
//               Ch08_06_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <immintrin.h>
#include "Ch08_06.h"

void MatrixMulF64_Cpp(MatrixF64& c, const MatrixF64& a, const MatrixF64& b)
{
    MatrixF64::Mul(c, a, b);
}

void MatrixMulF64_Iavx512(MatrixF64& c, const MatrixF64& a, const MatrixF64& b)
{
    if (!CheckArgs(c, a, b))
        throw std::runtime_error("MatrixMulF64_Iavx512() CheckArgs failed");

    const double* aa = a.Data();
    const double* bb = b.Data();
    double* cc = c.Data();

    size_t m = a.GetNumCols();
    size_t c_nrows = c.GetNumRows();
    size_t c_ncols = c.GetNumCols();
    size_t a_ncols = a.GetNumCols();
    size_t b_ncols = b.GetNumCols();

    const size_t num_simd_elements = 8;
    size_t num_residual_cols = c_ncols % num_simd_elements;

    // res_mask = 2 ** num_residual_cols - 1
    __mmask8 res_mask = (__mmask8)((1 << num_residual_cols) - 1);

    for (size_t i = 0; i < c_nrows; i++)
    {
        size_t j = 0;

        while (j + num_simd_elements <= c_ncols)
        {
            __m512d c_vals = _mm512_setzero_pd();

            for (size_t k = 0; k < m; k++)
            {
                __m512d a_vals = _mm512_set1_pd(aa[i * a_ncols + k]);
                __m512d b_vals = _mm512_loadu_pd(&bb[k * b_ncols + j]);
                
                c_vals = _mm512_fmadd_pd(a_vals, b_vals, c_vals);
            }

            _mm512_storeu_pd(&cc[i * c_ncols + j], c_vals);
            j += num_simd_elements;
        }

        if (num_residual_cols != 0)
        {
            __m512d c_vals = _mm512_setzero_pd();

            for (size_t k = 0; k < m; k++)
            {
                __m512d a_vals = _mm512_set1_pd(aa[i * a_ncols + k]);
                __m512d b_vals = _mm512_maskz_loadu_pd(res_mask, &bb[k * b_ncols + j]);
                
                c_vals = _mm512_fmadd_pd(a_vals, b_vals, c_vals);
            }

            _mm512_mask_storeu_pd(&cc[i * c_ncols + j], res_mask, c_vals);
        }
    }
}
