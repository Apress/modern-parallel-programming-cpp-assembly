//------------------------------------------------
//               Ch07_05_misc.cpp
//------------------------------------------------

#include "Ch07_05.h"
#include "AlignedMem.h"

bool CheckArgs(const ImageStats& im_stats)
{
    if (im_stats.m_NumPixels == 0)
        return false;
    if (im_stats.m_NumPixels % 64 != 0)
        return false;
    if (im_stats.m_NumPixels > c_NumPixelsMax)
        return false;
    if (!AlignedMem::IsAligned(im_stats.m_PixelBuffer, c_Alignment))
        return false;
    return true;
}
