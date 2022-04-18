//------------------------------------------------
//               Ch06_04_misc.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <stdexcept>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ch06_04.h"
#include "MT_Convolve.h"
#include "ImageMatrix.h"

bool CheckArgs1Dx2(const CD_1Dx2& cd)
{
    size_t im_src_size = cd.m_ImSrc.size();
    if (im_src_size != cd.m_ImDes.size())
        return false;
    if (im_src_size != cd.m_ImTmp.size())
        return false;
    if (im_src_size != cd.m_ImH * cd.m_ImW)
        return false;

    size_t ks = cd.m_KernelSize;
    if ((ks < 3) || ((ks & 0x1) == 0))
        return false;
    if ((cd.m_Kernel1Dx.size() != ks) || (cd.m_Kernel1Dy.size() != ks))
        return false;
    return true;
}

void Init1Dx2(std::array<CD_1Dx2, 2>& cd, const char* fn, KERNEL_ID id)
{
    GetKernel1Dx2(cd[0], id);
    GetKernel1Dx2(cd[1], id);

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
