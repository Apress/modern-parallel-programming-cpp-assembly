//------------------------------------------------
//               Ch19_02_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <immintrin.h>
#include "Ch19_02.h"
#include "MiscTypes.h"

void Convolve1Dx2_F32_Cpp(CD_1Dx2& cd)
{
    if (!CheckArgs1Dx2(cd))
        throw std::runtime_error("Convolve1Dx2_F32_Cpp() - CheckArgs failed");

    indx_t ks = (indx_t)cd.m_KernelSize;
    indx_t ks2 = ks / 2;
    indx_t im_h = cd.m_ImH;
    indx_t im_w = cd.m_ImW;
    const std::vector<float>& im_src = cd.m_ImSrc;
    std::vector<float>& im_des = cd.m_ImDes;
    std::vector<float>& im_tmp = cd.m_ImTmp;
    const std::vector<float>& im_ker_x = cd.m_Kernel1Dx;
    const std::vector<float>& im_ker_y = cd.m_Kernel1Dy;

    // Perform 1D convolution (X)
    for (indx_t i = ks2; i < im_h - ks2; i++)
    {
        for (indx_t j = ks2; j < im_w - ks2; j++)
        {
            float im_tmp_val = 0;

            for (indx_t k = -ks2; k <= ks2; k++)
                im_tmp_val += im_src[i * im_w + j - k] * im_ker_x[k + ks2];

            im_tmp[i * im_w + j] = im_tmp_val;
        }
    }

    // Perform 1D convolution (Y)
    for (indx_t j = ks2; j < im_w - ks2; j++)
    {
        for (indx_t i = ks2; i < im_h - ks2; i++)
        {
            float im_des_val = 0;

            for (indx_t k = -ks2; k <= ks2; k++)
                im_des_val += im_tmp[(i - k) * im_w + j] * im_ker_y[k + ks2];

            im_des[i * im_w + j] = im_des_val;
        }
    }
}

void Convolve1Dx2_F32a_Iavx512(CD_1Dx2& cd)
{
    if (!CheckArgs1Dx2(cd))
        throw std::runtime_error("Convolve1Dx2_F32a_Iavx512() - CheckArgs failed");

    indx_t ks = (indx_t)cd.m_KernelSize;
    indx_t ks2 = ks / 2;
    indx_t im_h = cd.m_ImH;
    indx_t im_w = cd.m_ImW;

    const std::vector<float>& im_src = cd.m_ImSrc;
    std::vector<float>& im_des = cd.m_ImDes;
    std::vector<float>& im_tmp = cd.m_ImTmp;
    const std::vector<float>& im_ker_x = cd.m_Kernel1Dx;
    const std::vector<float>& im_ker_y = cd.m_Kernel1Dy;

    const indx_t num_simd_elements = 16;
    const indx_t num_simd_elements2 = 8;
    const indx_t num_simd_elements3 = 4;

    // Perform 1D convolution (X)
    for (indx_t i = ks2; i < im_h - ks2; i++)
    {
        indx_t j = ks2;

        while (j < im_w - ks2)
        {
            if (j + num_simd_elements <= im_w - ks2)
            {
                __m512 im_tmp_vals = _mm512_setzero_ps();

                for (indx_t k = -ks2; k <= ks2; k++)
                {
                    __m512 im_src_vals = _mm512_loadu_ps(&im_src[i * im_w + j - k]);
                    __m512 im_ker_vals = _mm512_set1_ps(im_ker_x[k + ks2]);

                    im_tmp_vals = _mm512_fmadd_ps(im_src_vals, im_ker_vals,
                                    im_tmp_vals);
                }

                _mm512_storeu_ps(&im_tmp[i * im_w + j], im_tmp_vals);
                j += num_simd_elements;
            }
            else if (j + num_simd_elements2 <= im_w - ks2)
            {
                __m256 im_tmp_vals = _mm256_setzero_ps();

                for (indx_t k = -ks2; k <= ks2; k++)
                {
                    __m256 im_src_vals = _mm256_loadu_ps(&im_src[i * im_w + j - k]);
                    __m256 im_ker_vals = _mm256_set1_ps(im_ker_x[k + ks2]);

                    im_tmp_vals = _mm256_fmadd_ps(im_src_vals, im_ker_vals,
                                    im_tmp_vals);
                }

                _mm256_storeu_ps(&im_tmp[i * im_w + j], im_tmp_vals);
                j += num_simd_elements2;
            }
            else if (j + num_simd_elements3 <= im_w - ks2)
            {
                __m128 im_tmp_vals = _mm_setzero_ps();

                for (indx_t k = -ks2; k <= ks2; k++)
                {
                    __m128 im_src_vals = _mm_loadu_ps(&im_src[i * im_w + j - k]);
                    __m128 im_ker_vals = _mm_set1_ps(im_ker_x[k + ks2]);

                    im_tmp_vals = _mm_fmadd_ps(im_src_vals, im_ker_vals,
                                    im_tmp_vals);
                }

                _mm_storeu_ps(&im_tmp[i * im_w + j], im_tmp_vals);
                j += num_simd_elements3;
            }
            else
            {
                __m128 im_tmp_vals = _mm_setzero_ps();

                for (indx_t k = -ks2; k <= ks2; k++)
                {
                    __m128 im_src_vals = _mm_load_ss(&im_src[i * im_w + j - k]);
                    __m128 im_ker_vals = _mm_load_ss(&im_ker_x[k + ks2]);

                    im_tmp_vals = _mm_fmadd_ss(im_src_vals, im_ker_vals,
                                    im_tmp_vals);
                }

                _mm_store_ss(&im_tmp[i * im_w + j], im_tmp_vals);
                j += 1;
            }
        }
    }

    // Perform 1D convolution (Y)
    indx_t j = ks2;

    while (j < im_w - ks2)
    {
        if (j + num_simd_elements <= im_w - ks2)
        {
            for (indx_t i = ks2; i < im_h - ks2; i++)
            {
                __m512 im_des_vals = _mm512_setzero_ps();

                for (indx_t k = -ks2; k <= ks2; k++)
                {
                    __m512 im_tmp_vals = _mm512_loadu_ps(&im_tmp[(i - k) * im_w + j]);
                    __m512 im_ker_vals = _mm512_set1_ps(im_ker_y[k + ks2]);

                    im_des_vals = _mm512_fmadd_ps(im_tmp_vals, im_ker_vals,
                                    im_des_vals);
                }

                _mm512_storeu_ps(&im_des[i * im_w + j], im_des_vals);
             }

            j += num_simd_elements;
        }
        else if (j + num_simd_elements2 <= im_w - ks2)
        {
            for (indx_t i = ks2; i < im_h - ks2; i++)
            {
                __m256 im_des_vals = _mm256_setzero_ps();

                for (indx_t k = -ks2; k <= ks2; k++)
                {
                    __m256 im_tmp_vals = _mm256_loadu_ps(&im_tmp[(i - k) * im_w + j]);
                    __m256 im_ker_vals = _mm256_set1_ps(im_ker_y[k + ks2]);

                    im_des_vals = _mm256_fmadd_ps(im_tmp_vals, im_ker_vals,
                                    im_des_vals);
                }

                _mm256_storeu_ps(&im_des[i * im_w + j], im_des_vals);
             }

            j += num_simd_elements2;
        }
        else if (j + num_simd_elements3 <= im_w - ks2)
        {
            for (indx_t i = ks2; i < im_h - ks2; i++)
            {
                __m128 im_des_vals = _mm_setzero_ps();

                for (indx_t k = -ks2; k <= ks2; k++)
                {
                    __m128 im_tmp_vals = _mm_loadu_ps(&im_tmp[(i - k) * im_w + j]);
                    __m128 im_ker_vals = _mm_set1_ps(im_ker_y[k + ks2]);

                    im_des_vals = _mm_fmadd_ps(im_tmp_vals, im_ker_vals,
                                    im_des_vals);
                }

                _mm_storeu_ps(&im_des[i * im_w + j], im_des_vals);
             }

            j += num_simd_elements3;
        }
        else
        {
            for (indx_t i = ks2; i < im_h - ks2; i++)
            {
                __m128 im_des_vals = _mm_setzero_ps();

                for (indx_t k = -ks2; k <= ks2; k++)
                {
                    __m128 im_tmp_vals = _mm_load_ss(&im_tmp[(i - k) * im_w + j]);
                    __m128 im_ker_vals = _mm_load_ss(&im_ker_y[k + ks2]);

                    im_des_vals = _mm_fmadd_ss(im_tmp_vals, im_ker_vals,
                                    im_des_vals);
                }

                _mm_store_ss(&im_des[i * im_w + j], im_des_vals);
            }

            j += 1;
        }
    }
}
