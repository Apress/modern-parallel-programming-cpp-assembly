//------------------------------------------------
//               Ch06_01_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <immintrin.h>
#include "Ch06_01.h"
#include "MiscTypes.h"

void Convolve1D_F32_Cpp(std::vector<float>& y, const std::vector<float>& x, const std::vector<float>& kernel)
{
    if (!CheckArgs(y, x, kernel))
        throw std::runtime_error("Convolve1D_F32_Cpp() - CheckArgs failed");

    indx_t num_pts = (indx_t)y.size();
    indx_t ks2 = kernel.size() / 2;

    for (indx_t i = ks2; i < num_pts - ks2; i++)
    {
        float y_val = 0;

        for (indx_t k = -ks2; k <= ks2; k++)
            y_val += x[i - k] * kernel[k + ks2];

        y[i] = y_val;
    }
}

void Convolve1D_F32_Iavx2(std::vector<float>& y, const std::vector<float>& x, const std::vector<float>& kernel)
{
    if (!CheckArgs(y, x, kernel))
        throw std::runtime_error("Convolve1D_F32_Iavx2() - CheckArgs failed");

    indx_t ks2 = (indx_t)kernel.size() / 2;
    indx_t num_pts = (indx_t)y.size();
    const indx_t num_simd_elements = 8;
    const indx_t num_simd_elements2 = 4;

    indx_t i = ks2;

    while (i < num_pts - ks2)
    {
        if ((i + num_simd_elements) <= num_pts - ks2)
        {
             __m256 y_vals = _mm256_setzero_ps();

            // Calculate y[i:i+7]
            for (indx_t k = -ks2; k <= ks2; k++)
            {
                __m256 x_vals = _mm256_loadu_ps(&x[i - k]);
                __m256 kernel_vals = _mm256_set1_ps(kernel[k + ks2]);
                
                y_vals = _mm256_fmadd_ps(x_vals, kernel_vals, y_vals);
            }

            _mm256_storeu_ps(&y[i], y_vals);
            i += num_simd_elements;
        }
        else if ((i + num_simd_elements2) <= num_pts - ks2)
        {
             __m128 y_vals = _mm_setzero_ps();

            // Calculate y[i:i+3]
            for (indx_t k = -ks2; k <= ks2; k++)
            {
                __m128 x_vals = _mm_loadu_ps(&x[i - k]);
                __m128 kernel_vals = _mm_set1_ps(kernel[k + ks2]);
                
                y_vals = _mm_fmadd_ps(x_vals, kernel_vals, y_vals);
            }

            _mm_storeu_ps(&y[i], y_vals);
            i += num_simd_elements2;
        }
        else
        {
             __m128 y_val = _mm_setzero_ps();

            // Calculate y[i]
            for (indx_t k = -ks2; k <= ks2; k++)
            {
                __m128 x_val = _mm_load_ss(&x[i - k]);
                __m128 k_val = _mm_load_ss(&kernel[k + ks2]);
                y_val = _mm_fmadd_ss(x_val, k_val, y_val);
            }

            _mm_store_ss(&y[i], y_val);
            i += 1;
        }
    }
}

void Convolve1DKs5_F32_Iavx2(std::vector<float>& y, const std::vector<float>& x, const std::vector<float>& kernel)
{
    if (!CheckArgs(y, x, kernel))
        throw std::runtime_error("Convolve1DKs5_F32_Iavx2() - CheckArgs failed");
    if (kernel.size() != 5)
        throw std::runtime_error("Convolve1DKs5_F32_Iavx2() - invalid kernel size");

    const indx_t ks2 = 2;
    indx_t num_pts = (indx_t)y.size();
    const indx_t num_simd_elements = 8;
    const indx_t num_simd_elements2 = 4;

    __m256 kernel256_0 = _mm256_set1_ps(kernel[0]);
    __m256 kernel256_1 = _mm256_set1_ps(kernel[1]);
    __m256 kernel256_2 = _mm256_set1_ps(kernel[2]);
    __m256 kernel256_3 = _mm256_set1_ps(kernel[3]);
    __m256 kernel256_4 = _mm256_set1_ps(kernel[4]);

    __m128 kernel128_0 = _mm_set1_ps(kernel[0]);
    __m128 kernel128_1 = _mm_set1_ps(kernel[1]);
    __m128 kernel128_2 = _mm_set1_ps(kernel[2]);
    __m128 kernel128_3 = _mm_set1_ps(kernel[3]);
    __m128 kernel128_4 = _mm_set1_ps(kernel[4]);

    indx_t i = ks2;

    while (i < num_pts - ks2)
    {
        indx_t j = i + ks2;

        if ((i + num_simd_elements) <= num_pts - ks2)
        {
            // Calculate y[i:i+7]
            __m256 x_vals = _mm256_loadu_ps(&x[j]);
            __m256 y_vals = _mm256_mul_ps(x_vals, kernel256_0);

            x_vals = _mm256_loadu_ps(&x[j - 1]);
            y_vals = _mm256_fmadd_ps(x_vals, kernel256_1, y_vals);
            x_vals = _mm256_loadu_ps(&x[j - 2]);
            y_vals = _mm256_fmadd_ps(x_vals, kernel256_2, y_vals);
            x_vals = _mm256_loadu_ps(&x[j - 3]);
            y_vals = _mm256_fmadd_ps(x_vals, kernel256_3, y_vals);
            x_vals = _mm256_loadu_ps(&x[j - 4]);
            y_vals = _mm256_fmadd_ps(x_vals, kernel256_4, y_vals);

            _mm256_storeu_ps(&y[i], y_vals);
            i += num_simd_elements;
        }
        else if ((i + num_simd_elements2) <= num_pts - ks2)
        {
            // Calculate y[i:i+3]
            __m128 x_vals = _mm_loadu_ps(&x[j]);
            __m128 y_vals = _mm_mul_ps(x_vals, kernel128_0);

            x_vals = _mm_loadu_ps(&x[j - 1]);
            y_vals = _mm_fmadd_ps(x_vals, kernel128_1, y_vals);
            x_vals = _mm_loadu_ps(&x[j - 2]);
            y_vals = _mm_fmadd_ps(x_vals, kernel128_2, y_vals);
            x_vals = _mm_loadu_ps(&x[j - 3]);
            y_vals = _mm_fmadd_ps(x_vals, kernel128_3, y_vals);
            x_vals = _mm_loadu_ps(&x[j - 4]);
            y_vals = _mm_fmadd_ps(x_vals, kernel128_4, y_vals);

            _mm_storeu_ps(&y[i], y_vals);
            i += num_simd_elements2;
        }
        else
        {
            // Calculate y[i]
            __m128 x_val = _mm_load_ss(&x[j]);
            __m128 y_val = _mm_mul_ss(x_val, kernel128_0);

            x_val = _mm_load_ss(&x[j - 1]);
            y_val = _mm_fmadd_ss(x_val, kernel128_1, y_val);
            x_val = _mm_load_ss(&x[j - 2]);
            y_val = _mm_fmadd_ss(x_val, kernel128_2, y_val);
            x_val = _mm_load_ss(&x[j - 3]);
            y_val = _mm_fmadd_ss(x_val, kernel128_3, y_val);
            x_val = _mm_load_ss(&x[j - 4]);
            y_val = _mm_fmadd_ss(x_val, kernel128_4, y_val);

            _mm_store_ss(&y[i], y_val);
            i += 1;
        }
    }
}
