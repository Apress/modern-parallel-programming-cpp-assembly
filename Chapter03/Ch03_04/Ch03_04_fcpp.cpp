//------------------------------------------------
//               Ch03_04_fcpp.cpp
//------------------------------------------------

#include <cmath>
#include <immintrin.h>
#include "Ch03_04.h"

bool CalcMeanF32_Cpp(float* mean, const float* x, size_t n)
{
    if (!CheckArgs(x, n))
        return false;

    float sum = 0.0f;

    for (size_t i = 0; i < n; i++)
        sum += x[i];

    *mean = sum / n;
    return true;
}

bool CalcStDevF32_Cpp(float* st_dev, const float* x, size_t n, float mean)
{
    if (!CheckArgs(x, n))
        return false;

    float sum_squares = 0.0f;

    for (size_t i = 0; i < n; i++)
    {
        float temp = x[i] - mean;
        sum_squares += temp * temp;
    }

    *st_dev = sqrt(sum_squares / (n - 1));
    return true;
}

bool CalcMeanF32_Iavx(float* mean, const float* x, size_t n)
{
    if (!CheckArgs(x, n))
        return false;

    __m256 sums = _mm256_setzero_ps();

    size_t i = 0;
    const size_t num_simd_elements = 8;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256 x_vals = _mm256_load_ps(&x[i]);
        sums = _mm256_add_ps(x_vals, sums);
    }

    // Perform reduction, final sum in low-order element of temp4
    __m128 temp0 = _mm256_extractf128_ps(sums, 0);
    __m128 temp1 = _mm256_extractf128_ps(sums, 1);
    __m128 temp2 = _mm_add_ps(temp0, temp1);
    __m128 temp3 = _mm_hadd_ps(temp2, temp2);
    __m128 temp4 = _mm_hadd_ps(temp3, temp3);

    // Process remaining elements
    float sum;
    _mm_store_ss(&sum, temp4);

    for (; i < n; i++)
        sum += x[i];

    *mean = sum / n;
    return true;
}

bool CalcStDevF32_Iavx(float* st_dev, const float* x, size_t n, float mean)
{
    if (!CheckArgs(x, n))
        return false;

    __m256 packed_mean = _mm256_broadcast_ss(&mean);
    __m256 packed_sum_squares = _mm256_setzero_ps();

    size_t i = 0;
    const size_t num_simd_elements = 8;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256 x_vals = _mm256_load_ps(&x[i]);
        __m256 temp1 = _mm256_sub_ps(x_vals, packed_mean);
        __m256 temp2 = _mm256_mul_ps(temp1, temp1);

        packed_sum_squares = _mm256_add_ps(packed_sum_squares, temp2);
    }

    // Peform reduction, final sum_squares in low-order element of temp4
    __m128 temp0 = _mm256_extractf128_ps(packed_sum_squares, 0);
    __m128 temp1 = _mm256_extractf128_ps(packed_sum_squares, 1);
    __m128 temp2 = _mm_add_ps(temp0, temp1);
    __m128 temp3 = _mm_hadd_ps(temp2, temp2);
    __m128 temp4 = _mm_hadd_ps(temp3, temp3);

    // Process remaining elements
    float sum_squares;
    _mm_store_ss(&sum_squares, temp4);

    for (; i < n; i++)
    {
        float temp1 = x[i] - mean;
        sum_squares += temp1 * temp1;
    }

    *st_dev = sqrt(sum_squares / (n - 1));
    return true;
}
