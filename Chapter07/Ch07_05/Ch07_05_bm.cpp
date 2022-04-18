//------------------------------------------------
//               Ch07_05_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch07_05.h"
#include "BmThreadTimer.h"
#include "ImageMatrix.h"

void CalcImageStats_bm(void)
{
    std::cout << "\nRunning benchmark function CalcImageStats_bm - please wait\n";

    const char* image_fn = c_ImageFileName;

    ImageStats is1, is2;
    ImageMatrix im(image_fn, PixelType::Gray8);
    size_t num_pixels = im.GetNumPixels();
    uint8_t* pb = im.GetPixelBuffer<uint8_t>();

    is1.m_PixelBuffer = pb;
    is1.m_NumPixels = num_pixels;
    is1.m_PixelMinVal = c_PixelMinVal;
    is1.m_PixelMaxVal = c_PixelMaxVal;

    is2.m_PixelBuffer = pb;
    is2.m_NumPixels = num_pixels;
    is2.m_PixelMinVal = c_PixelMinVal;
    is2.m_PixelMaxVal = c_PixelMaxVal;

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        CalcImageStats_Cpp(is1);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        CalcImageStats_Iavx512(is2);
        bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch07_05_CalcImageStats_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
