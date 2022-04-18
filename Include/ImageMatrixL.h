//-------------------------------------------------
//               ImageMatrixL.h
//-------------------------------------------------

#pragma once
#include "ImageBuffer.h"
#include "ImageMisc.h"
#include "MF.h"

#if defined(__GNUG__)
#include "ImagePng.h"

class ImageMatrixL
{
    static const int c_PngTempBufferSize = 2048 * 2048 * sizeof(RGB32);     // h * w * sizeof(RGB32)

public:
    static void LoadImage(ImageBuffer& ib, const char* filename, PixelType pixel_type, Channel channel)
    {
        if (!MF::IsExt(filename, "png"))
            throw std::runtime_error("ImageMatrixL::LoadImage() - unsupported image file type");

        // TODO:
        // Update ImagePng to eliminate need for large temporary buffer.
        // ImagePng::LoadImage currently throws an exception if c_PngTempBufferSize
        // is too small.

        const int pb_png_size = c_PngTempBufferSize;
        uint8_t* pb_png = new uint8_t[pb_png_size];

        int height;
        int width;
        ImagePng im_png;
        im_png.LoadImage(filename, pb_png, pb_png_size, &height, &width);
        ib.Reallocate(height, width, pixel_type);

        uint8_t* pb_des = ib.GetPixelBuffer<uint8_t>();

        if (pixel_type == PixelType::Gray8)
        {
            int num_pixels = ib.GetNumPixels();

            for (int i = 0; i < num_pixels; i++)
                pb_des[i] = pb_png[i * 4 + (int)channel];
        }
        else
        {
            memcpy(pb_des, pb_png, ib.GetPixelBufferSize());
        }

        delete[] pb_png;
    }

    static void SaveImage(ImageBuffer& ib, const char* filename, ImageFileType file_type)
    {
        if (file_type != ImageFileType::PNG)
            throw std::runtime_error("ImageMatrixL::SaveImage() - unsupported file_type");

        int height = ib.GetHeight();
        int width = ib.GetWidth();
        int num_pixels = ib.GetNumPixels();
        PixelType pixel_type = ib.GetPixelType();
        uint8_t* pb_src = ib.GetPixelBuffer<uint8_t>();

        ImagePng im_png;

        if (pixel_type == PixelType::Gray8)
        {
            uint8_t* pb_png = new uint8_t[num_pixels * 4];

            for (int i = 0; i < num_pixels; i++)
            {
                pb_png[i * 4 + 0] = pb_src[i];
                pb_png[i * 4 + 1] = pb_src[i];
                pb_png[i * 4 + 2] = pb_src[i];
                pb_png[i * 4 + 3] = 0xff;
            }

            im_png.SaveImage(filename, pb_png, height, width);
            delete[] pb_png;
        }
        else if (pixel_type == PixelType::Rgb32)
        {
            im_png.SaveImage(filename, pb_src, height, width);
        }
        else
            throw std::runtime_error("ImageMatrixL::SaveImage() - unsupported pixel_type");
    }
};

#endif // defined(__GNUG__)
