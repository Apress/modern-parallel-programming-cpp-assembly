//------------------------------------------------
//               Ch16_02_test.cpp
//------------------------------------------------

#include <stdexcept>
#include <immintrin.h>
#include "Ch16_02.h"

const uint32_t ZR = 0;
const uint32_t MV = 0x80000000;

alignas(32) const uint32_t c_Mask0[8] {ZR, ZR, ZR, ZR, ZR, ZR, ZR, ZR};
alignas(32) const uint32_t c_Mask1[8] {MV, ZR, ZR, ZR, ZR, ZR, ZR, ZR};
alignas(32) const uint32_t c_Mask2[8] {MV, MV, ZR, ZR, ZR, ZR, ZR, ZR};
alignas(32) const uint32_t c_Mask3[8] {MV, MV, MV, ZR, ZR, ZR, ZR, ZR};
alignas(32) const uint32_t c_Mask4[8] {MV, MV, MV, MV, ZR, ZR, ZR, ZR};
alignas(32) const uint32_t c_Mask5[8] {MV, MV, MV, MV, MV, ZR, ZR, ZR};
alignas(32) const uint32_t c_Mask6[8] {MV, MV, MV, MV, MV, MV, ZR, ZR};
alignas(32) const uint32_t c_Mask7[8] {MV, MV, MV, MV, MV, MV, MV, ZR};

const uint32_t* c_MaskMovLUT[8]
{
    c_Mask0, c_Mask1, c_Mask2, c_Mask3, c_Mask4, c_Mask5, c_Mask6, c_Mask7
};

void MatrixMulF32p_Iavx2(MatrixF32& c, const MatrixF32& a, const MatrixF32& b)
{
    if (!CheckArgs(c, a, b))
        throw std::runtime_error("MatrixMulF32p_Iavx2() CheckArgs failed");

    const float* aa = a.Data();
    const float* bb = b.Data();
    float* cc = c.Data();
    size_t c_nrows = c.GetNumRows();
    size_t c_ncols = c.GetNumCols();
    size_t a_ncols = a.GetNumCols();
    size_t b_ncols = b.GetNumCols();

    const size_t num_simd_elements = 8;
    size_t num_residual_cols = c_ncols % num_simd_elements;
    __m256i res_mask = _mm256_load_si256((__m256i*)c_MaskMovLUT[num_residual_cols]);

    // Repeat for each row in c
    for (size_t i = 0; i < c_nrows; i++, aa += a_ncols)
    {
        size_t j = 0;

        // Repeat while there are at least NSE columns in current row of c
        while (j + num_simd_elements <= c_ncols)
        {
            const float* p_aa = aa;                 // &aa[i][0]
            const float* p_bb = &bb[j];             // &bb[0][j]

            __m256 c_vals = _mm256_setzero_ps();

            // Calculate products for c[i][j:j+7]
            for (size_t k = 0; k < a_ncols; k++)
            {
                __m256 a_vals = _mm256_broadcast_ss(p_aa);
                __m256 b_vals = _mm256_loadu_ps(p_bb);
            
                c_vals = _mm256_fmadd_ps(a_vals, b_vals, c_vals);
                p_aa++;
                p_bb += b_ncols;
            }

            _mm256_storeu_ps(cc, c_vals);
            j += num_simd_elements;
            cc += num_simd_elements;
        }

        if (num_residual_cols)
        {
            const float* p_aa = aa;                 // &aa[i][0]
            const float* p_bb = (float*)&bb[j];     // &bb[0][j]

            __m256 c_vals = _mm256_setzero_ps();

            // Calculate products for c[i][j:j+NRC]
            for (size_t k = 0; k < a_ncols; k++)
            {
                __m256 a_vals = _mm256_broadcast_ss(p_aa);
                __m256 b_vals = _mm256_maskload_ps(p_bb, res_mask);

                c_vals = _mm256_fmadd_ps(a_vals, b_vals, c_vals);
                p_aa++;
                p_bb += b_ncols;
            }

            _mm256_maskstore_ps(cc, res_mask, c_vals);
            cc += num_residual_cols;
        }
    }
}
