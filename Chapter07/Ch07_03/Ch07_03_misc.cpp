//------------------------------------------------
//               Ch07_03_misc.cpp
//------------------------------------------------

#include "Ch07_03.h"
#include "AlignedMem.h"

bool CheckArgs(const uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4])
{
    if (num_pixels > c_NumPixelsMax)
        return false;
    if (num_pixels % 16 != 0)
        return false;
    if (!AlignedMem::IsAligned(pb_gs, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pb_rgb, c_Alignment))
        return false;
    if (coef[0] < 0.0f || coef[1] < 0.0f || coef[2] < 0.0f)
        return false;
    return true;
}

bool CompareGsPixelBuffers(const uint8_t* pb_gs1, const uint8_t* pb_gs2, size_t num_pixels)
{
    for (size_t i = 0; i < num_pixels; i++)
    {
        if (abs((int)pb_gs1[i] - (int)pb_gs2[i]) > 1)
            return false;
    }
    return true;
}
