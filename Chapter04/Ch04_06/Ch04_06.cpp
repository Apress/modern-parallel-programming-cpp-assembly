//------------------------------------------------
//               Ch04_06.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Ch04_06.h"
#include "ImageMatrix.h"

const char* c_TestImageFileName = "../../Data/ImageA.png";

static void ProcessImage(void);

int main()
{
    try
    {
        ProcessImage();
        ProcessImage_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch04_06 exception: " << ex.what() << '\n';
    }
}

static void ProcessImage(void)
{
    const char nl = '\n';
    const char* fn_mask0 = "Ch04_06_ProcessImage_Mask0.png";
    const char* fn_mask1 = "Ch04_06_ProcessImage_Mask1.png";

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

    // Threshold image
    ThresholdImage_Cpp(&itd0);
    ThresholdImage_Iavx2(&itd1);
    im_mask0.SaveImage(fn_mask0, ImageFileType::PNG);
    im_mask1.SaveImage(fn_mask1, ImageFileType::PNG);

    // Calculate mean of masked pixels
    CalcImageMean_Cpp(&itd0);
    CalcImageMean_Iavx2(&itd1);

    const unsigned int w = 12;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\nResults for ProcessImage() using file ";
    std::cout  << c_TestImageFileName << nl << nl;
    std::cout << "                            Cpp         Iavx2\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "SumPixelsMasked:   ";
    std::cout << std::setw(w) << itd0.m_SumMaskedPixels << "  ";
    std::cout << std::setw(w) << itd1.m_SumMaskedPixels << nl;
    std::cout << "NumPixelsMasked:   ";
    std::cout << std::setw(w) << itd0.m_NumMaskedPixels << "  ";
    std::cout << std::setw(w) << itd1.m_NumMaskedPixels << nl;
    std::cout << "MeanMaskedPixels:  ";
    std::cout << std::setw(w) << itd0.m_MeanMaskedPixels << "  ";
    std::cout << std::setw(w) << itd1.m_MeanMaskedPixels << nl;
}
