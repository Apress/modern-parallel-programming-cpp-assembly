//------------------------------------------------
//               Ch07_03.cpp
//------------------------------------------------

#include <iostream>
#include <stdexcept>
#include "Ch07_03.h"
#include "ImageMatrix.h"

// Test image file
const char* c_TestImageFileName = "../../Data/ImageC.png";

// RGB to grayscale conversion coefficients, values must be positive
const float c_Coef[4] {0.2126f, 0.7152f, 0.0722f, 0.0f};

static void ConvertRgbToGs(void);

int main()
{
    try
    {
        ConvertRgbToGs();
        ConvertRgbToGs_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch07_03 exception: " << ex.what() << '\n';
    }
}

static void ConvertRgbToGs(void)
{
    const char nl = '\n';
    const char* fn_gs0 = "Ch07_03_GsImage0.png";
    const char* fn_gs1 = "Ch07_03_GsImage1.png";

    ImageMatrix im_rgb(c_TestImageFileName, PixelType::Rgb32);
    size_t im_h = im_rgb.GetHeight();
    size_t im_w = im_rgb.GetWidth();
    size_t num_pixels = im_h * im_w;

    ImageMatrix im_gs0(im_h, im_w, PixelType::Gray8);
    ImageMatrix im_gs1(im_h, im_w, PixelType::Gray8);
    RGB32* pb_rgb = im_rgb.GetPixelBuffer<RGB32>();
    uint8_t* pb_gs0 = im_gs0.GetPixelBuffer<uint8_t>();
    uint8_t* pb_gs1 = im_gs1.GetPixelBuffer<uint8_t>();

    std::cout << "Results for ConvertRgbToGs\n";
    std::cout << "  Converting RGB image " << c_TestImageFileName << nl;
    std::cout << "  im_h = " << im_h << " pixels\n";
    std::cout << "  im_w = " << im_w << " pixels\n";

    // Exercise conversion functions
    ConvertRgbToGs_Cpp(pb_gs0, pb_rgb, num_pixels, c_Coef);
    ConvertRgbToGs_Iavx512(pb_gs1, pb_rgb, num_pixels, c_Coef);

    std::cout << "Saving grayscale image #0 - " << fn_gs0 << nl;
    im_gs0.SaveImage(fn_gs0, ImageFileType::PNG);
    std::cout << "Saving grayscale image #1 - " << fn_gs1 << nl;
    im_gs1.SaveImage(fn_gs1, ImageFileType::PNG);

    if (CompareGsPixelBuffers(pb_gs0, pb_gs1, num_pixels))
        std::cout << "Grayscale pixel buffer compare OK\n";
    else
        std::cout << "Grayscale pixel buffer compare failed!\n";
}
