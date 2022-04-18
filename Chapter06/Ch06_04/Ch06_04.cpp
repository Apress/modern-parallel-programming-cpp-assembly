//------------------------------------------------
//               Ch06_04.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include "Ch06_04.h"
#include "ImageMatrix.h"

static void Convolve1Dx2_F32(void);

int main()
{
    try
    {
        Convolve1Dx2_F32();
        Convolve1Dx2_F32_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch06_04 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void Convolve1Dx2_F32(void)
{
    const char nl = '\n';
    const char* fn_src = "../../Data/ImageE.png";
    const char* fn_des0 = "Ch06_04_ImageE_Conv2D_0.png";
    const char* fn_des1 = "Ch06_04_ImageE_Conv2D_1.png";
    ImageFileType ift_des = ImageFileType::PNG;

    // Initialize convolution data structures
    std::array<CD_1Dx2, 2> cd;
    Init1Dx2(cd, fn_src, c_KernelID);

    // Perform convolutions
    std::cout << "Performing convolutions\n";
    Convolve1Dx2_F32_Cpp(cd[0]);
    Convolve1Dx2_F32_Iavx2(cd[1]);

    // Save destimation image files
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
    std::cout << std::boolalpha << "rc:       " << rc << nl;
    std::cout << "num_diff: " << num_diff << nl;
}
