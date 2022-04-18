//------------------------------------------------
//               Ch04_06_bm.cpp
//------------------------------------------------

#include <string>
#include "Ch04_06.h"
#include "BmThreadTimer.h"
#include "ImageMatrix.h"

void ProcessImage_bm(void)
{
    std::cout << "\nRunning benchmark function ProcessImage_Bm - please wait\n";

    ImageMatrix im_src(c_TestImageFileName, PixelType::Gray8);
    size_t im_h = im_src.GetHeight();
    size_t im_w = im_src.GetWidth();
    ImageMatrix im_mask0(im_h, im_w, PixelType::Gray8);
    ImageMatrix im_mask1(im_h, im_w, PixelType::Gray8);

    ITD itd0;
    itd0.m_PbSrc = im_src.GetPixelBuffer<uint8_t>();
    itd0.m_PbMask = im_mask0.GetPixelBuffer<uint8_t>();
    itd0.m_NumPixels = im_src.GetNumPixels();
    itd0.m_Threshold = c_TestThreshold;

    ITD itd1;
    itd1.m_PbSrc = im_src.GetPixelBuffer<uint8_t>();
    itd1.m_PbMask = im_mask1.GetPixelBuffer<uint8_t>();
    itd1.m_NumPixels = im_src.GetNumPixels();
    itd1.m_Threshold = c_TestThreshold;

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        ThresholdImage_Cpp(&itd0);
        CalcImageMean_Cpp(&itd0);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        ThresholdImage_Iavx2(&itd1);
        CalcImageMean_Iavx2(&itd1);
        bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch04_06_ProcessImage_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
