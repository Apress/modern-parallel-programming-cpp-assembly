//------------------------------------------------
//               Ch05_01_fcpp.cpp
//------------------------------------------------

#include <cmath>
#include <stdexcept>
#include <immintrin.h>
#include "Ch05_01.h"

void CalcLeastSquares_Cpp(double* m, double* b, const double* x, const double* y, size_t n)
{
    *m = 0.0;
    *b = 0.0;

    if (!CheckArgs(x, y, n))
        throw std::runtime_error("CalcLeastSquares_cpp() CheckArgs failed");

    double sum_x = 0.0, sum_y = 0.0, sum_xx = 0.0, sum_xy = 0.0;

    for (size_t i = 0; i < n; i++)
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_xx += x[i] * x[i];
        sum_xy += x[i] * y[i];
    }

    double denom = n * sum_xx - sum_x * sum_x;

    if (fabs(denom) >= c_LsEpsilon)
    {
        *m = (n * sum_xy - sum_x * sum_y) / denom;
        *b = (sum_xx * sum_y - sum_x * sum_xy) / denom;
    }
}

inline double SumF64x4(__m256d x)
{
    double sum;
    __m128d temp0 = _mm256_extractf128_pd(x, 0);
    __m128d temp1 = _mm256_extractf128_pd(x, 1);
    __m128d temp2 = _mm_add_pd(temp0, temp1);
    __m128d temp3 = _mm_hadd_pd(temp2, temp2);

    _mm_store_sd(&sum, temp3);
    return sum;
}

void CalcLeastSquares_Iavx2(double* m, double* b, const double* x, const double* y, size_t n)
{
    *m = 0.0;
    *b = 0.0;

    if (!CheckArgs(x, y, n))
        throw std::runtime_error("CalcLeastSquares_Iavx2() CheckArgs failed");

    __m256d packed_sum_x = _mm256_setzero_pd();
    __m256d packed_sum_y = _mm256_setzero_pd();
    __m256d packed_sum_xx = _mm256_setzero_pd();
    __m256d packed_sum_xy = _mm256_setzero_pd();

    size_t i = 0;
    const size_t num_simd_elements = 4;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256d x_vals = _mm256_load_pd(&x[i]);
        __m256d y_vals = _mm256_load_pd(&y[i]);

        packed_sum_x = _mm256_add_pd(packed_sum_x, x_vals);
        packed_sum_y = _mm256_add_pd(packed_sum_y, y_vals);
        packed_sum_xx = _mm256_fmadd_pd(x_vals, x_vals, packed_sum_xx);
        packed_sum_xy = _mm256_fmadd_pd(x_vals, y_vals, packed_sum_xy);
    }

    // Reduce packed sum values to scalars
    double sum_x = SumF64x4(packed_sum_x);
    double sum_y = SumF64x4(packed_sum_y);
    double sum_xx = SumF64x4(packed_sum_xx);
    double sum_xy = SumF64x4(packed_sum_xy);

    // Process final values
    for (; i < n; i++)
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_xx += x[i] * x[i];
        sum_xy += x[i] * y[i];
    }

    // Calculate slope and intercept
    double denom = n * sum_xx - sum_x * sum_x;

    if (fabs(denom) >= c_LsEpsilon)
    {
        *m = (n * sum_xy - sum_x * sum_y) / denom;
        *b = (sum_xx * sum_y - sum_x * sum_xy) / denom;
    }
}
