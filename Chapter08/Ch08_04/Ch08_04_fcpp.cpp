//------------------------------------------------
//               Ch08_04_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch08_04.h"

void CalcCovMatF64_Cpp(CMD& cmd)
{
    if (!CheckArgs(cmd))
        throw std::runtime_error("CalcCovMatrixF64_Cpp() - CheckArgs failed");

    size_t n_vars = cmd.m_X.GetNumRows();
    size_t n_obvs = cmd.m_X.GetNumCols();
    double* cov_mat = cmd.m_CovMat.Data();
    double* x = cmd.m_X.Data();
    double* var_means = cmd.m_VarMeans.data();

    // Calculate variable means (rows of cmd.m_X)
    for (size_t i = 0; i < n_vars; i++)
    {
        var_means[i] = 0.0;
        for (size_t j = 0; j < n_obvs; j++)
            var_means[i] += x[i * n_obvs + j];
        var_means[i] /= n_obvs;
    }

    // Calculate covariance matrix
    for (size_t i = 0; i < n_vars; i++)
    {
        for (size_t j = 0; j < n_vars; j++)
        {
            if (i <= j)
            {
                double sum = 0.0;

                for (size_t k = 0; k < n_obvs; k++)
                {
                    double temp1 = x[i * n_obvs + k] - var_means[i];
                    double temp2 = x[j * n_obvs + k] - var_means[j];
                    sum += temp1 * temp2;
                }

                cov_mat[i * n_vars + j] = sum / (n_obvs - 1);
            }
            else
                cov_mat[i * n_vars + j] = cov_mat[j * n_vars + i];
        }
    }
}

inline double ReduceAddF64(__m512d a, __m256d b, __m128d c)
{
    // Sum double precision values of arguments a, b, and c
    __m256d temp0 = _mm256_setzero_pd();
    __m256d temp1 = _mm256_insertf64x2(temp0, c, 0);
    __m256d temp2 = _mm256_add_pd(temp1, b);
    __m512d temp3 = _mm512_setzero_pd();
    __m512d temp4 = _mm512_insertf64x4(temp3, temp2, 0);
    __m512d temp5 = _mm512_add_pd(temp4, a);

    return _mm512_reduce_add_pd(temp5);
}

void CalcCovMatF64_Iavx512(CMD& cmd)
{
    if (!CheckArgs(cmd))
        throw std::runtime_error("CalcCovMatrixF64_Iavx512() - CheckArgs failed");

    size_t n_vars = cmd.m_X.GetNumRows();
    size_t n_obvs = cmd.m_X.GetNumCols();
    double* cov_mat = cmd.m_CovMat.Data();
    double* x = cmd.m_X.Data();
    double* var_means = cmd.m_VarMeans.data();
    const size_t num_simd_elements8 = 8;
    const size_t num_simd_elements4 = 4;
    const size_t num_simd_elements2 = 2;

    // Calculate variable means (rows of cmd.m_X)
    for (size_t i = 0; i < n_vars; i++)
    {
        size_t j = 0;
         __m512d sums_512 = _mm512_setzero_pd();
         __m256d sums_256 = _mm256_setzero_pd();
         __m128d sums_128 = _mm_setzero_pd();

        while (j < n_obvs)
        {
            if (n_obvs - j >= num_simd_elements8)
            {
                __m512d x_vals = _mm512_loadu_pd(&x[i * n_obvs + j]);
                sums_512 = _mm512_add_pd(x_vals, sums_512);
                j += num_simd_elements8;
            }
            else if (n_obvs - j >= num_simd_elements4)
            {
                __m256d x_vals = _mm256_loadu_pd(&x[i * n_obvs + j]);
                sums_256 = _mm256_add_pd(x_vals, sums_256);
                j += num_simd_elements4;
            }
            else if (n_obvs - j >= num_simd_elements2)
            {
                __m128d x_vals = _mm_loadu_pd(&x[i * n_obvs + j]);
                sums_128 = _mm_add_pd(x_vals, sums_128);
                j += num_simd_elements2;
            }
            else
            {
                __m128d x_val = _mm_load_sd(&x[i * n_obvs + j]);
                sums_128 = _mm_add_pd(x_val, sums_128);
                j += 1;
            }
        }

        double sum = ReduceAddF64(sums_512, sums_256, sums_128);
        var_means[i] = sum / n_obvs;
    }

    // Calculate covariance matrix
    for (size_t i = 0; i < n_vars; i++)
    {
        for (size_t j = 0; j < n_vars; j++)
        {
            if (i <= j)
            {
                size_t k = 0;
                __m512d sums_512 = _mm512_setzero_pd();
                __m256d sums_256 = _mm256_setzero_pd();
                __m128d sums_128 = _mm_setzero_pd();

                while (k < n_obvs)
                {
                    if (n_obvs - k >= num_simd_elements8)
                    {
                        __m512d var_means1_512 = _mm512_set1_pd(var_means[i]);
                        __m512d var_means2_512 = _mm512_set1_pd(var_means[j]);
                        __m512d x_vals1 = _mm512_loadu_pd(&x[i * n_obvs + k]);
                        __m512d x_vals2 = _mm512_loadu_pd(&x[j * n_obvs + k]);
                        __m512d temp1 = _mm512_sub_pd(x_vals1, var_means1_512);
                        __m512d temp2 = _mm512_sub_pd(x_vals2, var_means2_512);

                        sums_512 = _mm512_fmadd_pd(temp1, temp2, sums_512);
                        k += num_simd_elements8;
                    }
                    else if (n_obvs - k >= num_simd_elements4)
                    {
                        __m256d var_means1_256 = _mm256_set1_pd(var_means[i]);
                        __m256d var_means2_256 = _mm256_set1_pd(var_means[j]);
                        __m256d x_vals1 = _mm256_loadu_pd(&x[i * n_obvs + k]);
                        __m256d x_vals2 = _mm256_loadu_pd(&x[j * n_obvs + k]);
                        __m256d temp1 = _mm256_sub_pd(x_vals1, var_means1_256);
                        __m256d temp2 = _mm256_sub_pd(x_vals2, var_means2_256);

                        sums_256 = _mm256_fmadd_pd(temp1, temp2, sums_256);
                        k += num_simd_elements4;
                    }
                    else if (n_obvs - k >= num_simd_elements2)
                    {
                        __m128d var_means1_128 = _mm_set1_pd(var_means[i]);
                        __m128d var_means2_128 = _mm_set1_pd(var_means[j]);
                        __m128d x_vals1 = _mm_loadu_pd(&x[i * n_obvs + k]);
                        __m128d x_vals2 = _mm_loadu_pd(&x[j * n_obvs + k]);
                        __m128d temp1 = _mm_sub_pd(x_vals1, var_means1_128);
                        __m128d temp2 = _mm_sub_pd(x_vals2, var_means2_128);

                        sums_128 = _mm_fmadd_pd(temp1, temp2, sums_128);
                        k += num_simd_elements2;
                    }
                    else
                    {
                        __m128d var_means1_64 = _mm_load_sd(&var_means[i]);
                        __m128d var_means2_64 = _mm_load_sd(&var_means[j]);
                        __m128d x_vals1 = _mm_load_sd(&x[i * n_obvs + k]);
                        __m128d x_vals2 = _mm_load_sd(&x[j * n_obvs + k]);
                        __m128d temp1 = _mm_sub_pd(x_vals1, var_means1_64);
                        __m128d temp2 = _mm_sub_pd(x_vals2, var_means2_64);

                        sums_128 = _mm_fmadd_pd(temp1, temp2, sums_128);
                        k += 1;
                    }
                }

                double sum = ReduceAddF64(sums_512, sums_256, sums_128);
                cov_mat[i * n_vars + j] = sum / (n_obvs - 1);
            }
            else
                cov_mat[i * n_vars + j] = cov_mat[j * n_vars + i];
        }
    }
}
