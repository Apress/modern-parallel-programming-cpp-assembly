//------------------------------------------------
//               Ch03_05_fcpp.cpp
//------------------------------------------------

#include <cmath>
#include <xmmintrin.h>
#include <immintrin.h>
#include "Ch03_05.h"
#include "AlignedMem.h"

bool CalcMeanF64_Cpp(double* mean, const double* x, size_t n)
{
    if (!CheckArgs(x, n))
        return false;

    double sum = 0.0;

    for (size_t i = 0; i < n; i++)
        sum += x[i];

    *mean = sum / n;
    return true;
}

bool CalcStDevF64_Cpp(double* st_dev, const double* x, size_t n, double mean)
{
    if (!CheckArgs(x, n))
        return false;

    double sum_squares = 0.0;

    for (size_t i = 0; i < n; i++)
    {
        double temp = x[i] - mean;
        sum_squares += temp * temp;
    }

    *st_dev = sqrt(sum_squares / (n - 1));
    return true;
}

bool CalcMeanF64_Iavx(double* mean, const double* x, size_t n)
{
    if (!CheckArgs(x, n))
        return false;

    __m256d sums = _mm256_setzero_pd();

    size_t i = 0;
    const size_t num_simd_elements = 4;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256d x_vals = _mm256_load_pd(&x[i]);
        sums = _mm256_add_pd(x_vals, sums);
    }

    // Peform reduction, final sum in low-order element of temp3
    __m128d temp0 = _mm256_extractf128_pd(sums, 0);
    __m128d temp1 = _mm256_extractf128_pd(sums, 1);
    __m128d temp2 = _mm_add_pd(temp0, temp1);
    __m128d temp3 = _mm_hadd_pd(temp2, temp2);

    // Process remaining elements
    double sum;
    _mm_store_sd(&sum, temp3);

    for (; i < n; i++)
        sum += x[i];

    *mean = sum / n;
    return true;
}

bool CalcStDevF64_Iavx(double* st_dev, const double* x, size_t n, double mean)
{
    if (!CheckArgs(x, n))
        return false;

    __m256d packed_mean = _mm256_broadcast_sd(&mean);
    __m256d packed_sum_squares = _mm256_setzero_pd();

    size_t i = 0;
    const size_t num_simd_elements = 4;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256d x_vals = _mm256_load_pd(&x[i]);
        __m256d temp1 = _mm256_sub_pd(x_vals, packed_mean);
        __m256d temp2 = _mm256_mul_pd(temp1, temp1);

        packed_sum_squares = _mm256_add_pd(packed_sum_squares, temp2);
    }

    // Peform reduction, final sum_squares in low-order element of temp3
    __m128d temp0 = _mm256_extractf128_pd(packed_sum_squares, 0);
    __m128d temp1 = _mm256_extractf128_pd(packed_sum_squares, 1);
    __m128d temp2 = _mm_add_pd(temp0, temp1);
    __m128d temp3 = _mm_hadd_pd(temp2, temp2);

    // Process remaining elements
    double sum_squares;
    _mm_store_sd(&sum_squares, temp3);

    for (; i < n; i++)
    {
        double temp1 = x[i] - mean;
        sum_squares += temp1 * temp1;
    }

    *st_dev = sqrt(sum_squares / (n - 1));
    return true;
}
