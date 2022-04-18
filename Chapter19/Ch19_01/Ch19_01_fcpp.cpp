//------------------------------------------------
//               Ch19_01_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include <stdexcept>
#include "Ch19_01.h"
#include "MatrixF32.h"

void CalcRowStatsF32a_Iavx512(MatrixF32& x, std::vector<float>& row_means,
    std::vector<float>& row_sds)
{
    if (!CheckArgs(x, row_means, row_sds))
        throw std::runtime_error("CalcRowStatsF32a_Iavx512() - CheckArgs failed");

    size_t nrows = x.GetNumRows();
    size_t ncols = x.GetNumCols();
    const float* xx = x.Data();
    const size_t num_simd_elements = 16;

    for (size_t i = 0; i < nrows; i++)
    {
        // Calculate mean of row i in matrix x

        size_t j = 0;
         __m512 sums_f32x16 = _mm512_setzero_ps();

        // Repeat until fewer than 16 elements remain
        while (ncols - j >= num_simd_elements)
        {
            __m512 x_f32x16 = _mm512_loadu_ps(&xx[i * ncols + j]);

            sums_f32x16 = _mm512_add_ps(x_f32x16, sums_f32x16);
            j += num_simd_elements;
        }

        // 8 or more elements?
        if (ncols - j >= num_simd_elements / 2)
        {
            __m256 x_f32x8 = _mm256_loadu_ps(&xx[i * ncols + j]);
            __m512 x_f32x16 = _mm512_insertf32x8(_mm512_setzero_ps(), x_f32x8, 0);

            sums_f32x16 = _mm512_add_ps(x_f32x16, sums_f32x16);
            j += num_simd_elements / 2;
        }

        // 4 or more elements?
        if (ncols - j >= num_simd_elements / 4)
        {
            __m128 x_f32x4 = _mm_loadu_ps(&xx[i * ncols + j]);
            __m512 x_f32x16 = _mm512_insertf32x4(_mm512_setzero_ps(), x_f32x4, 0);

            sums_f32x16 = _mm512_add_ps(x_f32x16, sums_f32x16);
            j += num_simd_elements / 4;
        }

        // Reduce packed sums to scalar, then add any residual elements
        float sum = _mm512_reduce_add_ps(sums_f32x16);

        while (j < ncols)
        {
            sum += xx[i * ncols + j];
            j += 1;
        }

        row_means[i] = sum / ncols;

        // Calculate standard deviation of row i in matrix x

        j = 0;
        __m512 sum_sqs_f32x16 = _mm512_setzero_ps();
        __m512 row_means_f32x16 = _mm512_set1_ps(row_means[i]);

        // Repeat until fewer than 16 elements remain
        while (ncols - j >= num_simd_elements)
        {
            __m512 x_f32x16 = _mm512_loadu_ps(&xx[i * ncols + j]);
            __m512 t1_f32x16 = _mm512_sub_ps(x_f32x16, row_means_f32x16);
            __m512 t2_f32x16 = _mm512_mul_ps(t1_f32x16, t1_f32x16);

            sum_sqs_f32x16 = _mm512_add_ps(t2_f32x16, sum_sqs_f32x16);
            j += num_simd_elements;
        }

        // 8 or more elements?
        if (ncols - j >= num_simd_elements / 2)
        {
            __m256 x_f32x8 = _mm256_loadu_ps(&xx[i * ncols + j]);
            __m256 row_means_f32x8 = _mm256_set1_ps(row_means[i]);
            __m256 t1_f32x8 = _mm256_sub_ps(x_f32x8, row_means_f32x8);
            __m256 t2_f32x8 = _mm256_mul_ps(t1_f32x8, t1_f32x8);
            __m512 x_f32x16 = _mm512_insertf32x8(_mm512_setzero_ps(), t2_f32x8, 0);

            sum_sqs_f32x16 = _mm512_add_ps(x_f32x16, sum_sqs_f32x16);
            j += num_simd_elements / 2;
        }

        // 4 or more elements?
        if (ncols - j >= num_simd_elements / 4)
        {
            __m128 x_f32x4 = _mm_loadu_ps(&xx[i * ncols + j]);
            __m128 row_means_f32x4 = _mm_set1_ps(row_means[i]);
            __m128 t1_f32x4 = _mm_sub_ps(x_f32x4, row_means_f32x4);
            __m128 t2_f32x4 = _mm_mul_ps(t1_f32x4, t1_f32x4);
            __m512 x_f32x16 = _mm512_insertf32x4(_mm512_setzero_ps(), t2_f32x4, 0);

            sum_sqs_f32x16 = _mm512_add_ps(x_f32x16, sum_sqs_f32x16);
            j += num_simd_elements / 4;
        }

        // Reduce packed sum-of-squares to scalar, then add any residual elements
        float sum_sqs = _mm512_reduce_add_ps(sum_sqs_f32x16);

        while (j < ncols)
        {
            float temp1 = xx[i * ncols + j] - row_means[i];
            sum_sqs += temp1 * temp1;
            j += 1;
        }

        row_sds[i] =  sqrt(sum_sqs / (ncols - 1));
    }
}

void CalcRowStatsF32b_Iavx512(MatrixF32& x, std::vector<float>& row_means,
    std::vector<float>& row_sds)
{
    if (!CheckArgs(x, row_means, row_sds))
        throw std::runtime_error("CalcRowStatsF32b_Iavx512() - CheckArgs failed");

    size_t nrows = x.GetNumRows();
    size_t ncols = x.GetNumCols();
    const float* xx = x.Data();
    const size_t num_simd_elements = 16;

    for (size_t i = 0; i < nrows; i++)
    {
        // Calculate mean of row i in matrix x

        size_t j = 0;
         __m512 sums_f32x16 = _mm512_setzero_ps();

        // Repeat until fewer than 16 elements remain
        while (ncols - j >= num_simd_elements)
        {
            __m512 x_f32x16 = _mm512_loadu_ps(&xx[i * ncols + j]);

            sums_f32x16 = _mm512_add_ps(x_f32x16, sums_f32x16);
            j += num_simd_elements;
        }

        // Reduce packed sums to scalar, then add any residual elements
        float sum = _mm512_reduce_add_ps(sums_f32x16);

        while (j < ncols)
        {
            sum += xx[i * ncols + j];
            j += 1;
        }

        row_means[i] = sum / ncols;

        // Calculate standard deviation of row i in matrix x

        j = 0;
        __m512 sum_sqs_f32x16 = _mm512_setzero_ps();
        __m512 row_means_f32x16 = _mm512_set1_ps(row_means[i]);

        // Repeat until fewer than 16 elements remain
        while (ncols - j >= num_simd_elements)
        {
            __m512 x_f32x16 = _mm512_loadu_ps(&xx[i * ncols + j]);
            __m512 t1_f32x16 = _mm512_sub_ps(x_f32x16, row_means_f32x16);
            __m512 t2_f32x16 = _mm512_mul_ps(t1_f32x16, t1_f32x16);

            sum_sqs_f32x16 = _mm512_add_ps(t2_f32x16, sum_sqs_f32x16);
            j += num_simd_elements;
        }

        // Reduce packed sum-of-squares to scalar, then process residual elements
        float sum_sqs = _mm512_reduce_add_ps(sum_sqs_f32x16);

        while (j < ncols)
        {
            float temp1 = xx[i * ncols + j] - row_means[i];
            sum_sqs += temp1 * temp1;
            j += 1;
        }

        row_sds[i] =  sqrt(sum_sqs / (ncols - 1));
    }
}
