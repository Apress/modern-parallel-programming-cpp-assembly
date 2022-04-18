//------------------------------------------------
//               Ch17_03.cpp
//------------------------------------------------

#include <iostream>
#include <stdexcept>
#include <cassert>
#include "Ch17_03.h"
#include "AlignedMem.h"

// MENTION
//  Example XX_YY for image thresholding/mask image - this example exploits AVX-512 features

static void ComparePixels(void);

int main()
{
    try
    {
        ComparePixels();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch17_03 exception: " << ex.what() << '\n';
    }
}

static void ComparePixels(void)
{
    const size_t num_pixels = 4 * 1024 * 1024;

    AlignedArray<uint8_t> src_aa(num_pixels, c_Alignment);
    AlignedArray<uint8_t> des1_aa(num_pixels, c_Alignment);
    AlignedArray<uint8_t> des2_aa(num_pixels, c_Alignment);
    uint8_t* src = src_aa.Data();
    uint8_t* des1 = des1_aa.Data();
    uint8_t* des2 = des2_aa.Data();

    const uint8_t cmp_vals[] {197, 222, 43, 43, 129, 222};
    const CmpOp cmp_ops[] {CmpOp::EQ, CmpOp::NE, CmpOp::LT, CmpOp::LE, CmpOp::GT, CmpOp::GE};
    const size_t num_cmp_vals = sizeof(cmp_vals) / sizeof(uint8_t);
    const size_t num_cmp_ops = sizeof(cmp_ops) / sizeof(CmpOp);
    assert(num_cmp_vals == num_cmp_ops);

    InitArray(src, num_pixels, 511);

    std::cout << "Results for ComparePixels\n";

    for (size_t i = 0; i < num_cmp_ops; i++)
    {
        ComparePixels_Cpp(des1, src, num_pixels, cmp_ops[i], cmp_vals[i]);
        ComparePixels_Aavx512(des2, src, num_pixels, cmp_ops[i], cmp_vals[i]);
        DisplayResults(des1, des2, num_pixels, cmp_ops[i], cmp_vals[i], i + 1);
    }
}
