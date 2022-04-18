//------------------------------------------------
//               Ch18_06_fcpp.cpp
//------------------------------------------------

//!! MENTION

// Could have implemented NSE3 (as 4) code blocks but not done since easy to do & prog too long

#include <stdexcept>
#include <immintrin.h>
#include "Ch18_06.h"
#include "MiscTypes.h"

void Convolve1D_F32_Cpp(std::vector<float>& y, const std::vector<float>& x, const std::vector<float>& kernel)
{
    if (!CheckArgs(y, x, kernel))
        throw std::runtime_error("Convolve1D_F32_Cpp() - CheckArgs failed");

    indx_t num_pts = (indx_t)y.size();
    indx_t ks2 = kernel.size() / 2;

    for (indx_t i = 0; i < ks2; i++)
        y[i] = y[i + num_pts - ks2] = 0;

    for (indx_t i = ks2; i < num_pts - ks2; i++)
    {
        float y_val = 0;

        for (indx_t k = -ks2; k <= ks2; k++)
            y_val += x[i - k] * kernel[k + ks2];

        y[i] = y_val;
    }
}

void Convolve1D_F32_Iavx512(std::vector<float>& y, const std::vector<float>& x, const std::vector<float>& kernel)
{
    if (!CheckArgs(y, x, kernel))
        throw std::runtime_error("Convolve1D_F32_Iavx2() - CheckArgs failed");

    indx_t ks2 = (indx_t)kernel.size() / 2;
    indx_t num_pts = (indx_t)y.size();
    const indx_t num_simd_elements = 16;
    const indx_t num_simd_elements2 = 8;

    for (indx_t i = 0; i < ks2; i++)
        y[i] = y[i + num_pts - ks2] = 0;

    indx_t i = ks2;

    while (i < num_pts - ks2)
    {
        if ((i + num_simd_elements) <= num_pts - ks2)
        {
             __m512 y_vals = _mm512_setzero_ps();

            for (indx_t k = -ks2; k <= ks2; k++)
            {
                __m512 x_vals = _mm512_loadu_ps(&x[i - k]);
                __m512 kernel_vals = _mm512_set1_ps(kernel[k + ks2]);
                
                y_vals = _mm512_fmadd_ps(x_vals, kernel_vals, y_vals);
            }

            _mm512_storeu_ps(&y[i], y_vals);
            i += num_simd_elements;
        }
        else if ((i + num_simd_elements2) <= num_pts - ks2)
        {
             __m256 y_vals = _mm256_setzero_ps();

            for (indx_t k = -ks2; k <= ks2; k++)
            {
                __m256 x_vals = _mm256_loadu_ps(&x[i - k]);
                __m256 kernel_vals = _mm256_set1_ps(kernel[k + ks2]);
                
                y_vals = _mm256_fmadd_ps(x_vals, kernel_vals, y_vals);
            }

            _mm256_storeu_ps(&y[i], y_vals);
            i += num_simd_elements2;
        }
        else
        {
            float y_val = 0;

            for (indx_t k = -ks2; k <= ks2; k++)
                y_val += x[i - k] * kernel[k + ks2];

            y[i] = y_val;
            i += 1;
        }
    }
}

void Convolve1DKs5_F32_Iavx512(std::vector<float>& y, const std::vector<float>& x, const std::vector<float>& kernel)
{
    if (!CheckArgs(y, x, kernel))
        throw std::runtime_error("Convolve1DKs5_F32_Iavx2() - CheckArgs failed");

    if (kernel.size() != 5)
        throw std::runtime_error("Convolve1DKs5_F32_Iavx2() - invalid kernel size");

    indx_t ks2 = (indx_t)kernel.size() / 2;
    indx_t num_pts = (indx_t)y.size();
    const indx_t num_simd_elements = 16;
    const indx_t num_simd_elements2 = 8;

    // Fill edge elements with zeros
    for (indx_t i = 0; i < ks2; i++)
        y[i] = y[i + num_pts - ks2] = 0;

    // Load kernel elements
    __m512 kernel512_0 = _mm512_set1_ps(kernel[0]);
    __m512 kernel512_1 = _mm512_set1_ps(kernel[1]);
    __m512 kernel512_2 = _mm512_set1_ps(kernel[2]);
    __m512 kernel512_3 = _mm512_set1_ps(kernel[3]);
    __m512 kernel512_4 = _mm512_set1_ps(kernel[4]);

    indx_t i = ks2;

    while (i < num_pts - ks2)
    {
        indx_t j = i + ks2;

        if ((i + num_simd_elements) <= num_pts - ks2)
        {
            __m512 x_vals = _mm512_loadu_ps(&x[j]);
            __m512 y_vals = _mm512_mul_ps(x_vals, kernel512_0);

            x_vals = _mm512_loadu_ps(&x[j - 1]);
            y_vals = _mm512_fmadd_ps(x_vals, kernel512_1, y_vals);

            x_vals = _mm512_loadu_ps(&x[j - 2]);
            y_vals = _mm512_fmadd_ps(x_vals, kernel512_2, y_vals);

            x_vals = _mm512_loadu_ps(&x[j - 3]);
            y_vals = _mm512_fmadd_ps(x_vals, kernel512_3, y_vals);

            x_vals = _mm512_loadu_ps(&x[j - 4]);
            y_vals = _mm512_fmadd_ps(x_vals, kernel512_4, y_vals);

            _mm512_storeu_ps(&y[i], y_vals);
            i += num_simd_elements;
        }
        else if ((i + num_simd_elements2) <= num_pts - ks2)
        {
            __m256 kernel256_0 = _mm256_set1_ps(kernel[0]);
            __m256 kernel256_1 = _mm256_set1_ps(kernel[1]);
            __m256 kernel256_2 = _mm256_set1_ps(kernel[2]);
            __m256 kernel256_3 = _mm256_set1_ps(kernel[3]);
            __m256 kernel256_4 = _mm256_set1_ps(kernel[4]);

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
            i += num_simd_elements2;
        }
        else
        {
            float y_val = 0;

            for (indx_t k = -ks2; k <= ks2; k++)
                y_val += x[i - k] * kernel[k + ks2];

            y[i] = y_val;
            i += 1;
        }
    }
}
