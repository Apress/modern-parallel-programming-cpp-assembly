//------------------------------------------------
//               Ch04_04_bm.cpp
//------------------------------------------------

#include <iostream>
#include <string>
#include "Ch04_04.h"
#include "AlignedMem.h"
#include "MT.h"
#include "BmThreadTimer.h"

void ClipPixels_bm(void)
{
    std::cout << "\nRunning benchmark function ClipPixels_bm - please wait\n";

    const uint8_t thresh_lo = c_ThreshLo;
    const uint8_t thresh_hi = c_ThreshHi;
    const size_t num_pixels = c_NumPixelsBM;

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

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        ClipPixels_Cpp(&cd0);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        ClipPixels_Iavx2(&cd1);
        bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch04_04_ClipPixels_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
