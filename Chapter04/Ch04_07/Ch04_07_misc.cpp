//------------------------------------------------
//               Ch04_07_misc.cpp
//------------------------------------------------

#include <iostream>
#include "Ch04_07.h"
#include "AlignedMem.h"

float g_LUT_U8ToF32[256];

void BuildLUT_U8ToF32(void)
{
    size_t n = sizeof(g_LUT_U8ToF32) / sizeof(float);

    for (size_t i = 0; i < n; i++)
        g_LUT_U8ToF32[i] = (float)i / 255.0f;
}

bool CheckArgs(const void* pb1, const void* pb2, size_t num_pixels)
{
    if (num_pixels == 0 || num_pixels > c_NumPixelsMax)
        return false;
    if (!AlignedMem::IsAligned(pb1, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pb2, c_Alignment))
        return false;
    return true;
}

size_t CompareArraysF32(const float* pb_src1, const float* pb_src2, size_t num_pixels)
{
    size_t num_diff = 0;

    for (size_t i = 0; i < num_pixels; i++)
    {
        if (pb_src1[i] != pb_src2[i])
        {
            std::cout << i << ", " << pb_src1[i] << ", " << pb_src2[i] << '\n';
            num_diff++;
        }
    }

    return num_diff;
}
