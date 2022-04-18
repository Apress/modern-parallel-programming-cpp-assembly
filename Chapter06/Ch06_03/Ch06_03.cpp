//------------------------------------------------
//               Ch06_03.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Ch06_03.h"
#include "ImageMatrix.h"

static void Convolve2D_F32(void);

int main()
{
    try
    {
        Convolve2D_F32();
        Convolve2D_F32_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch06_03 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void Convolve2D_F32(void)
{
    const char nl = '\n';
    const char* fn_src = "../../Data/ImageE.png";
    const char* fn_des0 = "Ch06_03_ImageE_Conv2D_0.png";
    const char* fn_des1 = "Ch06_03_ImageE_Conv2D_1.png";
    ImageFileType ift_des = ImageFileType::PNG;

    // Initialize convolution data structures
    std::array<CD_2D, 2> cd;
    Init2D(cd, fn_src, c_KernelID);

    // Perform convolutions
    std::cout << "Performing convolutions\n";
    Convolve2D_F32_Cpp(cd[0]);
    Convolve2D_F32_Iavx2(cd[1]);

    // Save destination image files
    std::cout << "Saving destination image files\n";
    int h0 = (int)cd[0].m_ImH, w0 = (int)cd[0].m_ImW;
    int h1 = (int)cd[1].m_ImH, w1 = (int)cd[1].m_ImW;
    ImageMatrix im_des0 = ImageMatrix::ToImage(cd[0].m_ImDes, h0, w0, PixelType::Gray8);
    ImageMatrix im_des1 = ImageMatrix::ToImage(cd[1].m_ImDes, h1, w1, PixelType::Gray8);
    im_des0.SaveImage(fn_des0, ift_des);
    im_des1.SaveImage(fn_des1, ift_des);

    // Make sure images are alike.
    size_t num_diff;
    const uint8_t max_d = 1;
    bool rc = ImageMatrix::AreAlike(im_des0, im_des1, max_d, &num_diff);
    std::cout << "rc:       " << std::boolalpha << rc << nl;
    std::cout << "num_diff: " << num_diff << nl;
}
