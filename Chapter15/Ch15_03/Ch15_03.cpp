//------------------------------------------------
//               Ch15_03.cpp
//------------------------------------------------

#include <iostream>
#include <cstring>
#include <limits>
#include <stdexcept>
#include "Ch15_03.h"
#include "AlignedMem.h"
#include "MT.h"

static void ClipPixels(void);

int main()
{
    try
    {
        ClipPixels();
        ClipPixels_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch15_03 exception: " << ex.what() << '\n';
    }

}

static void ClipPixels(void)
{
    const char nl = '\n';
    const uint8_t thresh_lo = c_ThreshLo;
    const uint8_t thresh_hi = c_ThreshHi;
    const size_t num_pixels = c_NumPixels;

    AlignedArray<uint8_t> pb_src(num_pixels, c_Alignment);
    AlignedArray<uint8_t> pb_des0(num_pixels, c_Alignment);
    AlignedArray<uint8_t> pb_des1(num_pixels, c_Alignment);

    MT::FillArray(pb_src.Data(), num_pixels, c_RngMinVal, c_RngMaxVal, c_RngSeed);

    ClipData cd0, cd1;

    cd0.m_PbSrc = pb_src.Data();
    cd0.m_PbDes = pb_des0.Data();
    cd0.m_NumPixels = num_pixels;
    cd0.m_NumClippedPixels = (std::numeric_limits<size_t>::max)();
    cd0.m_ThreshLo = thresh_lo;
    cd0.m_ThreshHi = thresh_hi;

    cd1.m_PbSrc = pb_src.Data();
    cd1.m_PbDes = pb_des1.Data();
    cd1.m_NumPixels = num_pixels;
    cd1.m_NumClippedPixels = (std::numeric_limits<size_t>::max)();
    cd1.m_ThreshLo = thresh_lo;
    cd1.m_ThreshHi = thresh_hi;

    ClipPixels_Cpp(&cd0);
    ClipPixels_Aavx2(&cd1);

    std::cout << "\nResults for ClipPixels_Cpp\n";
    std::cout << "  cd0.m_NumClippedPixels: " << cd0.m_NumClippedPixels << nl;

    std::cout << "\nResults for ClipPixels_Aavx2\n";
    std::cout << "  cd1.m_NumClippedPixels: " << cd1.m_NumClippedPixels << nl;

    bool ncp_check1 = cd0.m_NumClippedPixels == cd1.m_NumClippedPixels;
    bool mem_check1 = memcmp(pb_des0.Data(), pb_des1.Data(), num_pixels) == 0;

    if (ncp_check1 && mem_check1) 
        std::cout << "\nResult compare checks passed\n";
    else
        std::cout << "\nResult compare checks failed!\n";
}
