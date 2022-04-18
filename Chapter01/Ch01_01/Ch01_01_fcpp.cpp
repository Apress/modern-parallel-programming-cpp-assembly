//------------------------------------------------
//               Ch01_01_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch01_01.h"

void CalcZ_Cpp(float* z, const float* x, const float* y, size_t n)
{
    for (size_t i = 0; i < n; i++)
        z[i] = x[i] + y[i];
}

void CalcZ_Iavx(float* z, const float* x, const float* y, size_t n)
{
    size_t i = 0;
    const size_t num_simd_elements = 8;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        // Calculate z[i:i+7] = x[i:i+7] + y[i:i+7]
        __m256 x_vals = _mm256_loadu_ps(&x[i]);
        __m256 y_vals = _mm256_loadu_ps(&y[i]);
        __m256 z_vals = _mm256_add_ps(x_vals, y_vals);

        _mm256_storeu_ps(&z[i], z_vals);
    }

    // Calculate z[i] = x[i] + y[i] for any remaining elements
    for (; i < n; i += 1)
        z[i] = x[i] + y[i];
}
