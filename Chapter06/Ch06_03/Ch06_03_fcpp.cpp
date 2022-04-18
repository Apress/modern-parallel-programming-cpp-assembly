//------------------------------------------------
//               Ch06_03_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <immintrin.h>
#include "Ch06_03.h"
#include "MiscTypes.h"

void Convolve2D_F32_Cpp(CD_2D& cd)
{
    if (!CheckArgs2D(cd))
        throw std::runtime_error("Convolve2D_F32_Cpp() - CheckArgs failed");

    indx_t ks = (indx_t)cd.m_KernelSize;
    indx_t ks2 = ks / 2;
    indx_t im_h = (indx_t)cd.m_ImH;
    indx_t im_w = (indx_t)cd.m_ImW;
    const std::vector<float>& im_src = cd.m_ImSrc;
    std::vector<float>& im_des = cd.m_ImDes;
    std::vector<float>& im_ker = cd.m_Kernel2D;

    for (indx_t i = ks2; i < im_h - ks2; i++)
    {
        for (indx_t j = ks2; j < im_w - ks2; j++)
        {
            float im_des_val = 0;

            for (indx_t k1 = -ks2; k1 <= ks2; k1++)
            {
                for (indx_t k2 = -ks2; k2 <= ks2; k2++)
                {
                    float im_src_val = im_src[(i - k1) * im_w + j - k2];
                    float im_ker_val = im_ker[(k1 + ks2) * ks + k2 + ks2];
                    
                    im_des_val += im_src_val * im_ker_val;
                }
            }

            im_des[i * im_w + j] = im_des_val;
        }
    }
}

void Convolve2D_F32_Iavx2(CD_2D& cd)
{
    if (!CheckArgs2D(cd))
        throw std::runtime_error("Convolve2D_F32_Iavx2() - CheckArgs failed");

    indx_t ks = (indx_t)cd.m_KernelSize;
    indx_t ks2 = ks / 2;
    indx_t im_h = (indx_t)cd.m_ImH;
    indx_t im_w = (indx_t)cd.m_ImW;
    const std::vector<float>& im_src = cd.m_ImSrc;
    std::vector<float>& im_des = cd.m_ImDes;
    std::vector<float>& im_ker = cd.m_Kernel2D;

    const indx_t num_simd_elements = 8;
    const indx_t num_simd_elements2 = 4;

    for (indx_t i = ks2; i < im_h - ks2; i++)
    {
        indx_t j = ks2;

        while (j < im_w - ks2)
        {
            if (j + num_simd_elements <= im_w - ks2)
            {
                __m256 im_des_vals = _mm256_setzero_ps();

                for (indx_t k1 = -ks2; k1 <= ks2; k1++)
                {
                    for (indx_t k2 = -ks2; k2 <= ks2; k2++)
                    {
                        indx_t i_src = (i - k1) * im_w + j - k2;
                        indx_t i_ker = (k1 + ks2) * ks + k2 + ks2;

                        __m256 im_src_vals = _mm256_loadu_ps(&im_src[i_src]);
                        __m256 im_ker_vals = _mm256_set1_ps(im_ker[i_ker]);

                        im_des_vals = _mm256_fmadd_ps(im_src_vals, im_ker_vals,
                                         im_des_vals);
                    }
                }

                _mm256_storeu_ps(&im_des[i * im_w + j], im_des_vals);
                j += num_simd_elements;
            }
            else if (j + num_simd_elements2 <= im_w - ks2)
            {
                __m128 im_des_vals = _mm_setzero_ps();

                for (indx_t k1 = -ks2; k1 <= ks2; k1++)
                {
                    for (indx_t k2 = -ks2; k2 <= ks2; k2++)
                    {
                        indx_t i_src = (i - k1) * im_w + j - k2;
                        indx_t i_ker = (k1 + ks2) * ks + k2 + ks2;

                        __m128 im_src_vals = _mm_loadu_ps(&im_src[i_src]);
                        __m128 im_ker_vals = _mm_set1_ps(im_ker[i_ker]);

                        im_des_vals = _mm_fmadd_ps(im_src_vals, im_ker_vals,
                                        im_des_vals);
                    }
                }

                _mm_storeu_ps(&im_des[i * im_w + j], im_des_vals);
                j += num_simd_elements2;
            }
            else
            {
                float im_des_val = 0;

                for (indx_t k1 = -ks2; k1 <= ks2; k1++)
                {
                    for (indx_t k2 = -ks2; k2 <= ks2; k2++)
                    {
                        indx_t i_src = (i - k1) * im_w + j - k2;
                        indx_t i_ker = (k1 + ks2) * ks + k2 + ks2;

                        float im_src_val = im_src[i_src];
                        float im_ker_val = im_ker[i_ker];

                        im_des_val += im_src_val * im_ker_val;
                    }
                }

                im_des[i * im_w + j] = im_des_val;
                j += 1;
            }
        }
    }
}
