//------------------------------------------------
//               Ch17_04_fcpp.cpp
//------------------------------------------------

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <immintrin.h>
#include "Ch17_04.h"

inline void CalcMeanStDev(ImageStats& im_stats)
{
    // Calculate mean and standard deviation
    double temp0 = (double)im_stats.m_NumPixelsInRange * im_stats.m_PixelSumSquares;
    double temp1 = (double)im_stats.m_PixelSum * im_stats.m_PixelSum;
    double var_num = temp0 - temp1;
    double var_den = (double)im_stats.m_NumPixelsInRange * (im_stats.m_NumPixelsInRange - 1);
    double var = var_num / var_den;

    im_stats.m_PixelMean = (double)im_stats.m_PixelSum / im_stats.m_NumPixelsInRange;
    im_stats.m_PixelStDev = sqrt(var);
}

void CalcImageStats_Cpp(ImageStats& im_stats)
{
    if (!CheckArgs(im_stats))
        throw std::runtime_error("CalcImageStats_Cpp() - CheckArgs failed");

    im_stats.m_PixelSum = 0;
    im_stats.m_PixelSumSquares = 0;
    im_stats.m_NumPixelsInRange = 0;

    size_t num_pixels = im_stats.m_NumPixels;
    const uint8_t* pb = im_stats.m_PixelBuffer;
 
    // Calculate intermediate sums
    for (size_t i = 0; i < num_pixels; i++)
    {
        uint32_t pval = pb[i];

        if (pval >= im_stats.m_PixelMinVal && pval <= im_stats.m_PixelMaxVal)
        {
            im_stats.m_PixelSum += pval;
            im_stats.m_PixelSumSquares += (uint64_t)pval * pval;
            im_stats.m_NumPixelsInRange++;
        }
    }

    CalcMeanStDev(im_stats);
}
