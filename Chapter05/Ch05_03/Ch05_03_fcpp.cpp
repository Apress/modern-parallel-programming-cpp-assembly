//------------------------------------------------
//               Ch05_03_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <immintrin.h>
#include "Ch05_03.h"

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

void MatrixMulF64_Cpp(MatrixF64& c, const MatrixF64& a, const MatrixF64& b)
{
    MatrixF64::Mul(c, a, b);
}

void MatrixMulF64_Iavx2(MatrixF64& c, const MatrixF64& a, const MatrixF64& b)
{
    if (!CheckArgs(c, a, b))
        throw std::runtime_error("MatrixMulF64_Iavx2() CheckArgs failed");

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

    // Repeat for each row in c
    for (size_t i = 0; i < c_nrows; i++)
    {
        size_t j = 0;

        // Repeat while 4 or more columns remain
        while (j + num_simd_elements <= c_ncols)
        {
            __m256d c_vals = _mm256_setzero_pd();

            // Calculate products for c[i][j:j+3]
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
}
