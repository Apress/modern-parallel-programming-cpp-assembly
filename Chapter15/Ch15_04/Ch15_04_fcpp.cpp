//------------------------------------------------
//               Ch15_04_fcpp.cpp
//------------------------------------------------

#include <iostream>
#include <stdexcept>
#include "Ch15_04.h"
#include "ImageMisc.h"

void ConvertRgbToGs_Cpp(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float coef[4])
{
    if (!CheckArgs(pb_gs, pb_rgb, num_pixels, coef))
        throw std::runtime_error("ConvertRgbToGs_Cpp() - CheckArgs failed");

    for (size_t i = 0; i < num_pixels; i++)
    {
        uint8_t r = pb_rgb[i].m_R;
        uint8_t g = pb_rgb[i].m_G;
        uint8_t b = pb_rgb[i].m_B;

        float gs_temp = r * coef[0] + g * coef[1] + b * coef[2] + 0.5f;

        if (gs_temp > 255.0f)
            gs_temp = 255.0f;

        pb_gs[i] = (uint8_t)gs_temp;
    }
}
