//------------------------------------------------
//               Ch08_09_misc.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <algorithm>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ch08_09.h"
#include "MT_Convolve.h"
#include "ImageMatrix.h"

bool CheckArgs1Dx2(const CD_1Dx2& cd)
{
    // Validate image buffer sizes
    size_t im_src_size = cd.m_ImSrc.size();

    if (im_src_size != cd.m_ImDes.size())
        return false;
    if (im_src_size != cd.m_ImTmp.size())
        return false;
    if (im_src_size != cd.m_ImH * cd.m_ImW)
        return false;

    // Validate kernel sizes
    size_t ks = cd.m_KernelSize;
    if ((ks < 3) || ((ks & 0x1) == 0))
        return false;
    if ((cd.m_Kernel1Dx.size() != ks) || (cd.m_Kernel1Dy.size() != ks))
        return false;
    return true;
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
    else
        throw std::runtime_error("GetKernel1Dx2() - invalid id");

#if defined(_DEBUG)
    std::cout << "\n----- Convolution Kernel -----\n"; 
    DisplayKernel1Dx2(sigma, cd.m_KernelSize);
#endif

}

void InitConvData1Dx2(std::array<CD_1Dx2, 2>& cd, const char* fn)
{
    GetKernel1Dx2(cd[0], KERNEL_ID::LowPass1Dx2_9x9);
    GetKernel1Dx2(cd[1], KERNEL_ID::LowPass1Dx2_9x9);

    ImageMatrix im_src0;

    if (fn != nullptr)
    {
        ImageMatrix im_tmp(fn, PixelType::Gray8);
        im_src0 = im_tmp;
    }
    else
    {
        ImageMatrix im_tmp(101, 103, PixelType::Gray8); // test image
        im_tmp.FillRandom(0, 255, 1003);
        im_src0 = im_tmp;
    }

    ImageMatrix im_src1(im_src0);

    im_src0.FillBorder<uint8_t>(cd[0].m_KernelSize / 2, (uint8_t)0);
    cd[0].m_ImH = im_src0.GetHeight();
    cd[0].m_ImW = im_src0.GetWidth();
    cd[0].m_ImSrc = im_src0.ToVector<float>();
    cd[0].m_ImDes.resize(cd[0].m_ImSrc.size());
    std::fill(cd[0].m_ImDes.begin(), cd[0].m_ImDes.end(), 0.0f);
    cd[0].m_ImTmp.resize(cd[0].m_ImSrc.size());
    std::fill(cd[0].m_ImTmp.begin(), cd[0].m_ImTmp.end(), 0.0f);

    im_src1.FillBorder<uint8_t>(cd[1].m_KernelSize / 2, (uint8_t)0);
    cd[1].m_ImH = im_src1.GetHeight();
    cd[1].m_ImW = im_src1.GetWidth();
    cd[1].m_ImSrc = im_src1.ToVector<float>();
    cd[1].m_ImDes.resize(cd[1].m_ImSrc.size());
    std::fill(cd[1].m_ImDes.begin(), cd[1].m_ImDes.end(), 0.0f);
    cd[1].m_ImTmp.resize(cd[1].m_ImSrc.size());
    std::fill(cd[1].m_ImTmp.begin(), cd[1].m_ImTmp.end(), 0.0f);
}
