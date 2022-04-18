//------------------------------------------------
//               Ch15_05.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Ch15_05.h"
#include "AlignedMem.h"
#include "MT.h"

static void ConvertU8ToF32();

int main()
{
    try
    {
        BuildLUT_U8ToF32();
        ConvertU8ToF32();
        ConvertU8ToF32_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch15_05 exception: " << ex.what() << '\n';
    }
}

static void ConvertU8ToF32()
{
    const char nl = '\n';
    size_t num_pixels = c_NumPixels;
    AlignedArray<uint8_t> pb_src_aa(num_pixels, c_Alignment);
    AlignedArray<float> pb_des0_aa(num_pixels, c_Alignment);
    AlignedArray<float> pb_des1_aa(num_pixels, c_Alignment);
    uint8_t* pb_src = pb_src_aa.Data();
    float* pb_des0 = pb_des0_aa.Data();
    float* pb_des1 = pb_des1_aa.Data();

    MT::FillArray(pb_src, num_pixels, c_FillMinVal, c_FillMaxVal, c_RngSeed); 

    ConvertU8ToF32_Cpp(pb_des0, pb_src, num_pixels);
    ConvertU8ToF32_Aavx2(pb_des1, pb_src, num_pixels);

    std::cout << "\nResults for ConvertU8ToF32\n";
    size_t num_diff = CompareArraysF32(pb_des0, pb_des1, num_pixels);
    std::cout << "  num_pixels:  " << num_pixels << nl;
    std::cout << "  num_diff:    " << num_diff << nl;
}
