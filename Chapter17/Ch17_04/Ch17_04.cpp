//------------------------------------------------
//               Ch17_04.cpp
//------------------------------------------------

// Mention
//  SD formula ok for integer arith, not suitable for FP

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Ch17_04.h"
#include "ImageMatrix.h"

const char* c_ImageFileName = "../../Data/ImageB.png";
static void CalcImageStats(void);

int main()
{
    try
    {
        CalcImageStats();
        CalcImageStats_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch17_04 exception: " << ex.what() << '\n';
    }
}

static void CalcImageStats(void)
{
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

    const char nl = '\n';
    const char* s = " | ";
    const unsigned int w1 = 22;
    const unsigned int w2 = 12;

    std::cout << std::fixed << std::setprecision(6) << std::left;

    std::cout << "\nResults for CalcImageStats\n";
    std::cout << std::setw(w1) << "image_fn:" << std::setw(w2) << image_fn << nl;
    std::cout << std::setw(w1) << "num_pixels:" << std::setw(w2) << num_pixels << nl;
    std::cout << std::setw(w1) << "c_PixelMinVal:" << std::setw(w2) << c_PixelMinVal << nl;
    std::cout << std::setw(w1) << "c_PixelMaxVal:" <<  std::setw(w2) << c_PixelMaxVal << nl;
    std::cout << nl;

    CalcImageStats_Cpp(is1);
    CalcImageStats_Aavx512(is2);

    std::cout << std::setw(w1) << "m_NumPixelsInRange: ";
    std::cout << std::setw(w2) << is1.m_NumPixelsInRange << s;
    std::cout << std::setw(w2) << is2.m_NumPixelsInRange << nl;

    std::cout << std::setw(w1) << "m_PixelSum:";
    std::cout << std::setw(w2) << is1.m_PixelSum << s;
    std::cout << std::setw(w2) << is2.m_PixelSum << nl;

    std::cout << std::setw(w1) << "m_PixelSumSquares:";
    std::cout << std::setw(w2) << is1.m_PixelSumSquares << s;
    std::cout << std::setw(w2) << is2.m_PixelSumSquares << nl;

    std::cout << std::setw(w1) << "m_PixelMean:";
    std::cout << std::setw(w2) << is1.m_PixelMean << s;
    std::cout << std::setw(w2) << is2.m_PixelMean << nl;
    
    std::cout << std::setw(w1) << "m_PixelStDev:";
    std::cout << std::setw(w2) << is1.m_PixelStDev << s;
    std::cout << std::setw(w2) << is2.m_PixelStDev << nl;
}
