//------------------------------------------------
//               Ch15_05_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include "Ch15_05.h"

void ConvertU8ToF32_Cpp(float* pb_des, const uint8_t* pb_src, size_t num_pixels)
{
    if (!CheckArgs(pb_des, pb_src, num_pixels))
        throw std::runtime_error("ConvertU8ToF32_Cpp() CheckArgs failed");

    const float* lut = g_LUT_U8ToF32;

    for (size_t i = 0; i < num_pixels; i++)
        pb_des[i] = lut[pb_src[i]];
}
