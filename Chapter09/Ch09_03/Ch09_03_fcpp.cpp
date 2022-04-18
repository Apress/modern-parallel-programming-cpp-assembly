//------------------------------------------------
//               Ch09_03_fcpp.cpp
//------------------------------------------------

#include <iostream>
#include <immintrin.h>
#include <cmath>
#include "Ch09_03.h"
#include "SimdMath.h"

void CalcBSA_F64_Cpp(std::vector<double>& bsa, const std::vector<double>& ht,
    const std::vector<double>& wt)
{
    if (!CheckArgs(bsa, ht, wt))
        throw std::runtime_error("CalcBSA_F64_Cpp() - CheckArgs failed");
    
    size_t n = ht.size();

    for (size_t i = 0; i < n; i++)
    {
        bsa[(n * 0) + i] = 0.007184 * pow(ht[i], 0.725) * pow(wt[i], 0.425);
        bsa[(n * 1) + i] = 0.0235 * pow(ht[i], 0.42246) * pow(wt[i], 0.51456);
        bsa[(n * 2) + i] = sqrt(ht[i] * wt[i] / 3600.0);
    }
}

void CalcBSA_F64_Iavx(std::vector<double>& bsa, const std::vector<double>& ht,
    const std::vector<double>& wt)
{
    if (!CheckArgs(bsa, ht, wt))
        throw std::runtime_error("CalcBSA_F64_Iavx() - CheckArgs failed");

    __m256d f64_0p007184 = _mm256_set1_pd(0.007184);
    __m256d f64_0p725 = _mm256_set1_pd(0.725);
    __m256d f64_0p425 = _mm256_set1_pd(0.425);
    __m256d f64_0p0235 = _mm256_set1_pd(0.0235);
    __m256d f64_0p42246 = _mm256_set1_pd(0.42246);
    __m256d f64_0p51456 = _mm256_set1_pd(0.51456);
    __m256d f64_3600p0 = _mm256_set1_pd(3600.0);

    size_t i = 0;
    size_t n = ht.size();
    const size_t num_simd_elements = 4;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256d ht_vals = _mm256_loadu_pd(&ht[i]);
        __m256d wt_vals = _mm256_loadu_pd(&wt[i]);

        __m256d temp1 = pow_f64x4(ht_vals, f64_0p725);
        __m256d temp2 = pow_f64x4(wt_vals, f64_0p425);
        __m256d temp3 = _mm256_mul_pd(temp1, temp2);
        __m256d bsa_vals = _mm256_mul_pd(f64_0p007184, temp3);
        _mm256_storeu_pd(&bsa[(n * 0) + i], bsa_vals);

        temp1 = pow_f64x4(ht_vals, f64_0p42246);
        temp2 = pow_f64x4(wt_vals, f64_0p51456);
        temp3 = _mm256_mul_pd(temp1, temp2);
        bsa_vals = _mm256_mul_pd(f64_0p0235, temp3);
        _mm256_storeu_pd(&bsa[(n * 1) + i], bsa_vals);

        temp1 = _mm256_mul_pd(ht_vals, wt_vals);
        temp2 = _mm256_div_pd(temp1, f64_3600p0);
        bsa_vals = _mm256_sqrt_pd(temp2);
        _mm256_storeu_pd(&bsa[(n * 2) + i], bsa_vals);
    }

    for (; i < n; i++)
    {
        bsa[(n * 0) + i] = 0.007184 * pow(ht[i], 0.725) * pow(wt[i], 0.425);
        bsa[(n * 1) + i] = 0.0235 * pow(ht[i], 0.42246) * pow(wt[i], 0.51456);
        bsa[(n * 2) + i] = sqrt(ht[i] * wt[i] / 3600.0);
    }
}
