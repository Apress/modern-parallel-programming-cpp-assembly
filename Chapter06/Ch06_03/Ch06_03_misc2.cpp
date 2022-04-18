//------------------------------------------------
//               Ch06_03_misc2.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include "Ch06_03.h"
#include "MT_Convolve.h"

void DisplayKernel2D(float sigma, size_t ks)
{
    std::vector<float> gk = GenGaussianKernel2D(sigma, ks);

    std::cout << std::fixed << std::setprecision(6);

    float sum = 0.0f;
    for (size_t i = 0; i < ks; i++)
    {
        for (size_t j = 0; j < ks; j++)
        {
            sum += gk[i * ks + j];
            std::cout << std::setw(10) << gk[i * ks + j] << ' ';
        }

        std::cout << '\n';
    }

    std::cout << "  sum = " << sum << "\n\n";
}

void GetKernel2D(CD_2D& cd, KERNEL_ID id)
{
    float sigma;

    if (id == KERNEL_ID::LowPass2D_3x3)
    {
        sigma = 0.5f;
        cd.m_KernelSize = 3;
        cd.m_Kernel2D = GenGaussianKernel2D(sigma, cd.m_KernelSize);
    }
    else if (id == KERNEL_ID::LowPass2D_5x5)
    {
        sigma = 1.0f;
        cd.m_KernelSize = 5;
        cd.m_Kernel2D = GenGaussianKernel2D(sigma, cd.m_KernelSize);
    }
    else if (id == KERNEL_ID::LowPass2D_7x7)
    {
        sigma = 2.0f;
        cd.m_KernelSize = 7;
        cd.m_Kernel2D = GenGaussianKernel2D(sigma, cd.m_KernelSize);
    }
    else if (id == KERNEL_ID::LowPass2D_9x9)
    {
        sigma = 3.0f;
        cd.m_KernelSize = 9;
        cd.m_Kernel2D = GenGaussianKernel2D(sigma, cd.m_KernelSize);
    }
    else if (id == KERNEL_ID::LowPass2D_15x15)
    {
        sigma = 11.0f;
        cd.m_KernelSize = 15;
        cd.m_Kernel2D = GenGaussianKernel2D(sigma, cd.m_KernelSize);
    }
    else
        throw std::runtime_error("GetKernel2D() - invalid id");

#if defined(_DEBUG)
    std::cout << "\n----- Convolution Kernel -----\n"; 
    DisplayKernel2D(sigma, cd.m_KernelSize);
#endif
}
