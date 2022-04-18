//------------------------------------------------
//               Ch15_03_fcpp.cpp
//------------------------------------------------

#include "Ch15_03.h"
#include "AlignedMem.h"

void ClipPixels_Cpp(ClipData* clip_data)
{
    if (!CheckArgs(clip_data))
        throw std::runtime_error("ClipPixels_Cpp() - CheckArgs failed");

    uint8_t* pb_src = clip_data->m_PbSrc;
    uint8_t* pb_des = clip_data->m_PbDes;
    size_t num_pixels = clip_data->m_NumPixels;
    size_t num_clipped_pixels = 0;
    uint8_t thresh_lo = clip_data->m_ThreshLo;
    uint8_t thresh_hi = clip_data->m_ThreshHi;

    for (size_t i = 0; i < num_pixels; i++)
    {
        uint8_t pixel = pb_src[i];

        if (pixel < thresh_lo)
        {
            pb_des[i] = thresh_lo;
            num_clipped_pixels++;
        }
        else if (pixel > thresh_hi)
        {
            pb_des[i] = thresh_hi;
            num_clipped_pixels++;
        }
        else
            pb_des[i] = pb_src[i];
    }

    clip_data->m_NumClippedPixels = num_clipped_pixels;
}
