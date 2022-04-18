//------------------------------------------------
//               Ch06_04_misc2.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include "Ch06_04.h"
#include "MT_Convolve.h"

void DisplayKernel1Dx2(float sigma, size_t ks)
{
    std::vector<float> gk = GenGaussianKernel1D(sigma, ks);

    std::cout << std::fixed << std::setprecision(6);

    float sum = 0.0f;
    for (size_t i = 0; i < ks; i++)
    {
        sum += gk[i];
        std::cout << std::setw(10) << gk[i] << ' ';
    }

    std::cout << '\n';
    std::cout << "  sum = " << sum << "\n\n";
}

void GetKernel1Dx2(CD_1Dx2& cd, KERNEL_ID id)
{
    float sigma;

    if (id == KERNEL_ID::LowPass1Dx2_3x3)
    {
        sigma = 0.5f;
        cd.m_KernelSize = 3;
        cd.m_Kernel1Dx = GenGaussianKernel1D(sigma, cd.m_KernelSize);
        cd.m_Kernel1Dy = cd.m_Kernel1Dx;
    }
    else if (id == KERNEL_ID::LowPass1Dx2_5x5)
    {
        sigma = 1.0f;
        cd.m_KernelSize = 5;
        cd.m_Kernel1Dx = GenGaussianKernel1D(sigma, cd.m_KernelSize);
        cd.m_Kernel1Dy = cd.m_Kernel1Dx;
    }
    else if (id == KERNEL_ID::LowPass1Dx2_7x7)
    {
        sigma = 2.0f;
        cd.m_KernelSize = 7;
        cd.m_Kernel1Dx = GenGaussianKernel1D(sigma, cd.m_KernelSize);
        cd.m_Kernel1Dy = cd.m_Kernel1Dx;
    }
    else if (id == KERNEL_ID::LowPass1Dx2_9x9)
    {
        sigma = 3.0f;
        cd.m_KernelSize = 9;
        cd.m_Kernel1Dx = GenGaussianKernel1D(sigma, cd.m_KernelSize);
        cd.m_Kernel1Dy = cd.m_Kernel1Dx;
    }
    else if (id == KERNEL_ID::LowPass1Dx2_15x15)
    {
        sigma = 11.0f;
        cd.m_KernelSize = 15;
        cd.m_Kernel1Dx = GenGaussianKernel1D(sigma, cd.m_KernelSize);
        cd.m_Kernel1Dy = cd.m_Kernel1Dx;
    }
    else
        throw std::runtime_error("GetKernel1Dx2() - invalid id");

#if defined(_DEBUG)
    std::cout << "\n----- Convolution Kernel -----\n"; 
    DisplayKernel1Dx2(sigma, cd.m_KernelSize);
#endif
}

