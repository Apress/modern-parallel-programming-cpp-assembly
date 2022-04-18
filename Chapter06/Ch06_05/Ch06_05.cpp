//------------------------------------------------
//               Ch06_05.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "ImageMatrix.h"

static void CompareConvolutionImages(void);

int main()
{
    try
    {
        CompareConvolutionImages();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch06_05 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void CompareConvolutionImages(void)
{
    const PixelType pt = PixelType::Gray8;
    const char* im0_fn = "../Ch06_03/Ch06_03_ImageE_Conv2D_0.png";
    const char* im1_fn = "../Ch06_03/Ch06_03_ImageE_Conv2D_1.png";
    const char* im2_fn = "../Ch06_04/Ch06_04_ImageE_Conv2D_0.png";
    const char* im3_fn = "../Ch06_04/Ch06_04_ImageE_Conv2D_1.png";

    const char nl = '\n';
    std::cout << "Comparing convolution result images\n";
    std::cout << im0_fn << nl;
    std::cout << im1_fn << nl;
    std::cout << im2_fn << nl;
    std::cout << im3_fn << nl;

    ImageMatrix im0(im0_fn, pt);
    ImageMatrix im1(im1_fn, pt);
    ImageMatrix im2(im2_fn, pt);
    ImageMatrix im3(im3_fn, pt);

    const uint8_t max_d = 1;
    size_t num_diff_0_1, num_diff_0_2, num_diff_0_3;
    bool rc_0_1 = ImageMatrix::AreAlike(im0, im1, max_d, &num_diff_0_1);
    bool rc_0_2 = ImageMatrix::AreAlike(im0, im2, max_d, &num_diff_0_2);
    bool rc_0_3 = ImageMatrix::AreAlike(im0, im3, max_d, &num_diff_0_3);

    if (!rc_0_1 || !rc_0_2 || !rc_0_3)
        std::cout << "\nInvalid return code from ImageMatrix::AreAlike()\n";
    else
    {
        if (num_diff_0_1 == 0 && num_diff_0_2 == 0 && num_diff_0_3 == 0)
            std::cout << "\nAll images are alike\n";
        else
        {
            std::cout << "Images differences detected!\n";
            std::cout << "num_diff_0_1: " << num_diff_0_1 << nl;
            std::cout << "num_diff_0_2: " << num_diff_0_2 << nl;
            std::cout << "num_diff_0_3: " << num_diff_0_3 << nl;
        }
    }
}
