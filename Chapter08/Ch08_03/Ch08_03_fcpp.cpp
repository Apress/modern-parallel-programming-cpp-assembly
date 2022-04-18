//------------------------------------------------
//               Ch08_03_fcpp.cpp
//------------------------------------------------

#include <cmath>
#include <stdexcept>
#include <immintrin.h>
#include "Ch08_03.h"
#include "AlignedMem.h"

void CalcMeanF32_Cpp(float* mean, const float* x, size_t n)
{
    if (!CheckArgs(x, n))
        throw std::runtime_error("CalcMeanF32_Cpp() - CheckArgs failed");

    float sum = 0.0f;

    for (size_t i = 0; i < n; i++)
        sum += x[i];

    *mean = sum / n;
}

void CalcStDevF32_Cpp(float* st_dev, const float* x, size_t n, float mean)
{
    if (!CheckArgs(x, n))
        throw std::runtime_error("CalcStDevF32_Cpp() - CheckArgs failed");

    float sum_squares = 0.0f;

    for (size_t i = 0; i < n; i++)
    {
        float temp = x[i] - mean;
        sum_squares += temp * temp;
    }

    *st_dev = sqrt(sum_squares / (n - 1));
}

void CalcMeanF32_Iavx512(float* mean, const float* x, size_t n)
{
    if (!CheckArgs(x, n))
        throw std::runtime_error("CalcMeanF32_Iavx512() - CheckArgs failed");

    __m512 sums = _mm512_setzero_ps();

    size_t i = 0;
    const size_t num_simd_elements = 16;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m512 x_vals = _mm512_load_ps(&x[i]);
        sums = _mm512_add_ps(x_vals, sums);
    }

    // Reduce packed sums to scalar value, then process remaining elements
    float sum = _mm512_reduce_add_ps(sums);

    for (; i < n; i++)
        sum += x[i];

    *mean = sum / n;
}

void CalcStDevF32_Iavx512(float* st_dev, const float* x, size_t n, float mean)
{
    if (!CheckArgs(x, n))
        throw std::runtime_error("CalcStDevF32_Iavx512() - CheckArgs failed");

    __m512 packed_mean = _mm512_set1_ps(mean);
    __m512 packed_sum_squares = _mm512_setzero_ps();

    size_t i = 0;
    const size_t num_simd_elements = 16;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m512 x_vals = _mm512_load_ps(&x[i]);
        __m512 temp1 = _mm512_sub_ps(x_vals, packed_mean);

        packed_sum_squares = _mm512_fmadd_ps(temp1, temp1, packed_sum_squares);
    }

    // Reduce packed_sum_squares to scalar value, then process remaining elements
    float sum_squares =_mm512_reduce_add_ps(packed_sum_squares);

    for (; i < n; i++)
    {
        float temp1 = x[i] - mean;
        sum_squares += temp1 * temp1;
    }

    *st_dev = sqrt(sum_squares / (n - 1));
}
