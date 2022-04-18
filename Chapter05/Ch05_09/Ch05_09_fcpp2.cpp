//------------------------------------------------
//               Ch05_09_fcpp2.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch05_09.h"

// This file contains AVX2 implementations of MatrixF64 functions
// that are used by the matrix inversion algorithm

// Mask values and LUT for _mm256_maskload_pd
const uint64_t ZR = 0;
const uint64_t MV = 0x8000000000000000;

alignas(32) const uint64_t c_Mask0[4] {ZR, ZR, ZR, ZR};
alignas(32) const uint64_t c_Mask1[4] {MV, ZR, ZR, ZR};
alignas(32) const uint64_t c_Mask2[4] {MV, MV, ZR, ZR};
alignas(32) const uint64_t c_Mask3[4] {MV, MV, MV, ZR};

const uint64_t* c_MaskMovLUT[8]
{
    c_Mask0, c_Mask1, c_Mask2, c_Mask3,
};

MatrixF64 MatrixAddF64_Iavx2(const MatrixF64& a, const MatrixF64& b)
{
    size_t nrows = a.GetNumRows();
    size_t ncols = a.GetNumCols();
    MatrixF64 c(nrows, ncols);

    const double* aa = a.Data();
    const double* bb = b.Data();
    double* cc = c.Data();
    const size_t n = c.GetNumElements();

    size_t i = 0;
    const size_t num_simd_elements = 4;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256d a_vals = _mm256_load_pd(&aa[i]);
        __m256d b_vals = _mm256_load_pd(&bb[i]);
        __m256d c_vals = _mm256_add_pd(a_vals, b_vals);

        _mm256_store_pd(&cc[i], c_vals);
    }

    // Process final elements
    for (; i < n; i++)
        cc[i] = aa[i] + bb[i];

    return c;
}

MatrixF64 MatrixMulF64_Iavx2(const MatrixF64& a, const MatrixF64& b)
{
    MatrixF64 c(a.GetNumRows(), b.GetNumCols());

    const double* aa = a.Data();
    const double* bb = b.Data();
    double* cc = c.Data();
    size_t c_nrows = c.GetNumRows();
    size_t c_ncols = c.GetNumCols();
    size_t a_ncols = a.GetNumCols();
    size_t b_ncols = b.GetNumCols();

    const size_t num_simd_elements = 4;
    size_t num_residual_cols = c_ncols % num_simd_elements;
    __m256i res_mask = _mm256_load_si256((__m256i*)c_MaskMovLUT[num_residual_cols]);

    for (size_t i = 0; i < c_nrows; i++)
    {
        size_t j = 0;

        while (j + num_simd_elements <= c_ncols)
        {
            __m256d c_vals = _mm256_setzero_pd();

            for (size_t k = 0; k < a_ncols; k++)
            {
                __m256d a_vals = _mm256_broadcast_sd(&aa[i * a_ncols + k]);
                __m256d b_vals = _mm256_loadu_pd(&bb[k * b_ncols + j]);
                
                c_vals = _mm256_fmadd_pd(a_vals, b_vals, c_vals);
            }

            _mm256_storeu_pd(&cc[i * c_ncols + j], c_vals);
            j += num_simd_elements;
        }

        if (num_residual_cols)
        {
            __m256d c_vals = _mm256_setzero_pd();

            for (size_t k = 0; k < a_ncols; k++)
            {
                __m256d a_vals = _mm256_broadcast_sd(&aa[i * a_ncols + k]);
                __m256d b_vals = _mm256_maskload_pd(&bb[k * b_ncols + j], res_mask);
                
                c_vals = _mm256_fmadd_pd(a_vals, b_vals, c_vals);
            }

            _mm256_maskstore_pd(&cc[i * c_ncols + j], res_mask, c_vals);
        }
    }

    return c;
}

void MatrixMulScalarF64_Iavx2(MatrixF64& c, const MatrixF64& a, double s_val)
{
    const double* aa = a.Data();
    double* cc = c.Data();
    const size_t n = a.GetNumElements();

    size_t i = 0;
    const size_t num_simd_elements = 4;

    __m256d s_vals = _mm256_broadcast_sd(&s_val);

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256d a_vals = _mm256_load_pd(&aa[i]);
        __m256d c_vals = _mm256_mul_pd(a_vals, s_vals);

        _mm256_store_pd(&cc[i], c_vals);
    }

    // Process final elements
    for (; i < n; i++)
        cc[i] = aa[i] * s_val;
}
