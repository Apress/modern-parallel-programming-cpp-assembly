//------------------------------------------------
//               Ch19_02.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include "Ch19_02.h"
#include "ImageMatrix.h"

const char* c_TestImageFileName = nullptr; // "../../Data/ImageE.png";

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
        std::cout << "Ch19_02 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void Convolve1Dx2_F32(void)
{
    const char nl = '\n';
    const char* fn_src = c_TestImageFileName;
    const char* fn_des0 = "Ch19_02_Conv2D_0.png";
    const char* fn_des1 = "Ch19_02_Conv2D_1.png";
    const char* fn_des2 = "Ch19_02_Conv2D_2.png";
    ImageFileType ift_des = ImageFileType::PNG;

    // Initialize convolution data structures
    std::array<CD_1Dx2, 3> cd;
    InitConvData1Dx2(cd, fn_src);

    // Perform convolutions
    std::cout << "Performing convolutions\n";
    Convolve1Dx2_F32_Cpp(cd[0]);
    Convolve1Dx2_F32a_Iavx512(cd[1]);
    Convolve1Dx2_F32b_Iavx512(cd[2]);

    // Save destimation image files
    std::cout << "Saving destination image files\n";
    int h0 = (int)cd[0].m_ImH, w0 = (int)cd[0].m_ImW;
    int h1 = (int)cd[1].m_ImH, w1 = (int)cd[1].m_ImW;
    int h2 = (int)cd[2].m_ImH, w2 = (int)cd[2].m_ImW;
    ImageMatrix im_des0 = ImageMatrix::ToImage(cd[0].m_ImDes, h0, w0, PixelType::Gray8);
    ImageMatrix im_des1 = ImageMatrix::ToImage(cd[1].m_ImDes, h1, w1, PixelType::Gray8);
    ImageMatrix im_des2 = ImageMatrix::ToImage(cd[2].m_ImDes, h2, w2, PixelType::Gray8);
    im_des0.SaveImage(fn_des0, ift_des);
    im_des1.SaveImage(fn_des1, ift_des);
    im_des2.SaveImage(fn_des2, ift_des);

    // Make sure images are alike.
    size_t num_diff_0_1;
    size_t num_diff_1_2;
    const uint8_t max_d = 1;
    bool b0_1 = ImageMatrix::AreAlike(im_des0, im_des1, max_d, &num_diff_0_1);
    bool b1_2 = ImageMatrix::AreAlike(im_des1, im_des2, max_d, &num_diff_1_2);

    if (b0_1 && b1_2)
        std::cout << "Image compare test passed" << nl;
    else
        std::cout << "Image compare test FAILED!" << nl;

    std::cout << "num_diff_0_1 = " << num_diff_0_1 << nl;
    std::cout << "num_diff_1_2 = " << num_diff_1_2 << nl;
}
