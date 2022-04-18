//-------------------------------------------------
//               ImageMatrixW.h
//-------------------------------------------------

#pragma once
#include <cstdint>
#include <stdexcept>
#include <cwchar>
#include "MF.h"
#include "ImageBuffer.h"

#if defined(_MSC_VER)
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib, "Gdiplus.lib")

class ImageMatrixW
{
    static const wchar_t* GetFormatString(ImageFileType file_type)
    {
        if (file_type == ImageFileType::BMP)
            return L"image/bmp";

        if (file_type == ImageFileType::PNG)
            return L"image/png";

        if (file_type == ImageFileType::JPEG)
            return L"image/jpeg";

        if (file_type == ImageFileType::TIFF)
            return L"image/tiff";

        throw std::runtime_error("ImageMatrixW::GetFormatString() - unsupported file_type");
    }

    static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
    {
        int rc = -1;
        unsigned int size;
        unsigned int num_encoders;

        Gdiplus::GetImageEncodersSize(&num_encoders, &size);

        if (size > 0)
        {
            Gdiplus::ImageCodecInfo* image_codec_info = (Gdiplus::ImageCodecInfo*)malloc(size);
            
            if (image_codec_info != NULL)
            {
                Gdiplus::GetImageEncoders(num_encoders, size, image_codec_info);

                for (unsigned int i = 0; i < num_encoders; i++)
                {
                    Gdiplus::ImageCodecInfo* p = &image_codec_info[i];
                    const WCHAR* mime_type = p->MimeType;

                    if (std::wcscmp(mime_type, format) == 0)
                    {
                        rc = i;
                        *pClsid = image_codec_info[i].Clsid;
                        break;
                    }
                }

               free(image_codec_info);
            }    
        }

        return rc;
    }

public:
    static void LoadImage(ImageBuffer& ib, const char* filename, PixelType pixel_type, Channel channel)
    {
        ULONG_PTR GdiToken;
        Gdiplus::GdiplusStartupInput GdiInput;
        Gdiplus::Status status = Gdiplus::GdiplusStartup(&GdiToken, &GdiInput, NULL);

        if (status == Gdiplus::Ok)
        {
            std::string ex_msg;
            Gdiplus::Bitmap* bm = nullptr;
            bool ex_occurred = false;

            try
            {
                std::wstring filename2 = MF::ToWstring(filename);
                bm =  new Gdiplus::Bitmap(filename2.c_str(), FALSE);

                if (bm->GetLastStatus() != Gdiplus::Status::Ok)
                    throw std::runtime_error("ImageMatrixW::LoadImage() - bitmap create failed");

                Gdiplus::PixelFormat pixel_format = bm->GetPixelFormat();

                if (pixel_format == PixelFormat8bppIndexed)
                {
                    ib.Reallocate(bm->GetHeight(), bm->GetWidth(), PixelType::Gray8);
                    uint8_t* pb = ib.GetPixelBuffer<uint8_t>();

                    for (size_t i = 0; i < ib.GetHeight(); i++)
                    {
                        for (size_t j = 0; j < ib.GetWidth(); j++)
                        {
                            Gdiplus::Color c;

                            if (bm->GetPixel((INT)j, (INT)i, &c) != Gdiplus::Ok)
                                throw std::runtime_error("ImageMatrixW::LoadImage - Bitmap::GetPixel() error occurred");

                            *pb++ = c.GetGreen();
                        }
                    }
                }
                else if (pixel_format == PixelFormat24bppRGB)
                {
                    if (channel == Channel::R || channel == Channel::G || channel == Channel::B)
                    {
                        ib.Reallocate(bm->GetHeight(), bm->GetWidth(), PixelType::Gray8);
                        uint8_t* pb = ib.GetPixelBuffer<uint8_t>();

                        for (size_t i = 0; i < ib.GetHeight(); i++)
                        {
                            for (size_t j = 0; j < ib.GetWidth(); j++)
                            {
                                Gdiplus::Color c;

                                if (bm->GetPixel((INT)j, (INT)i, &c) != Gdiplus::Ok)
                                    throw std::runtime_error("ImageMatrixW::LoadImage - Bitmap::GetPixel() error occurred");

                                uint8_t temp;

                                if (channel == Channel::R)
                                    temp = c.GetRed();
                                else if (channel == Channel::G)
                                    temp = c.GetGreen();
                                else
                                    temp = c.GetBlue();

                                *pb++ = temp;
                            }
                        }
                    }
                    else if (channel == Channel::None)
                    {
                        ib.Reallocate(bm->GetHeight(), bm->GetWidth(), PixelType::Rgb32);
                        RGB32* pb = ib.GetPixelBuffer<RGB32>();

                        for (size_t i = 0; i < ib.GetHeight(); i++)
                        {
                            for (size_t j = 0; j < ib.GetWidth(); j++)
                            {
                                RGB32 rgb;
                                Gdiplus::Color c;

                                if (bm->GetPixel((INT)j, (INT)i, &c) != Gdiplus::Ok)
                                    throw std::runtime_error("ImageMatrixW::LoadImage - Bitmap::GetPixel() error occurred");

                                rgb.m_R = c.GetRed();
                                rgb.m_G = c.GetGreen();
                                rgb.m_B = c.GetBlue();
                                rgb.m_A = 0xff;

                                *pb++ = rgb;
                            }
                        }
                    }
                    else
                        throw std::runtime_error("ImageMatrixW::LoadImage - Invalid channel");
                }
                else if (pixel_format == PixelFormat32bppARGB)
                {
                    // Note: GDI+ converts indexed (256 colors) PNG files to PixelFormat32bppARGB during load.
                    if (MF::IsPngFile(filename))
                    {
                        ib.Reallocate(bm->GetHeight(), bm->GetWidth(), PixelType::Gray8);
                        uint8_t* pb = ib.GetPixelBuffer<uint8_t>();

                        for (size_t i = 0; i < ib.GetHeight(); i++)
                        {
                            for (size_t j = 0; j < ib.GetWidth(); j++)
                            {
                                Gdiplus::Color c;

                                if (bm->GetPixel((INT)j, (INT)i, &c) != Gdiplus::Ok)
                                    throw std::runtime_error("ImageMatrixW::LoadImage - Bitmap::GetPixel() error occurred");

                                *pb++ = c.GetGreen();
                            }
                        }
                    }
                    else
                        throw std::runtime_error("ImageMatrixW::LoadImage() - unsupported pixel_format");
                }
            }

            catch (const std::exception& ex)
            {
                ex_msg = ex.what();
                ex_occurred = true;
            }

            // Bitmap must be deleted before GdiplusShutdown.
            if (bm != nullptr)
                delete bm;

            Gdiplus::GdiplusShutdown(GdiToken);

            if (ex_occurred)
                throw std::runtime_error(ex_msg); 
        }
    }

    static void SaveImage(ImageBuffer& ib, const char* filename, ImageFileType file_type)
    {
        ULONG_PTR GdiToken;
        Gdiplus::GdiplusStartupInput GdiInput;
        Gdiplus::Status status = Gdiplus::GdiplusStartup(&GdiToken, &GdiInput, NULL);

        if (status == Gdiplus::Ok)
        {
            std::string ex_msg;
            Gdiplus::Bitmap* bm = nullptr;
            bool ex_occurred = false;

            try
            {
                size_t ib_width = ib.GetWidth();
                size_t ib_height = ib.GetHeight();
                PixelType ib_pixel_type = ib.GetPixelType();
                Gdiplus::BitmapData bitmapData;
                Gdiplus::Rect rect(0, 0, (INT)ib_width, (INT)ib_height);

                if (ib_pixel_type == PixelType::Gray8)
                {
                    if (file_type == ImageFileType::PNG)
                    {
                        uint8_t* pb_src = ib.GetPixelBuffer<uint8_t>();
                        bm = new Gdiplus::Bitmap((INT)ib_width, (INT)ib_height, PixelFormat32bppRGB);

                        if (bm->GetLastStatus() != Gdiplus::Status::Ok)
                            throw std::runtime_error("ImageMatrixW::SaveImage() - bitmap create failed (#1)");

                        for (size_t i = 0; i < ib_height; i++)
                        {
                            for (size_t j = 0; j < ib_width; j++)
                            {
                                uint8_t pval = *pb_src++;
                                Gdiplus::Color c(0xff, pval, pval, pval);

                                if (bm->SetPixel((INT)j, (INT)i, c) != Gdiplus::Ok)
                                    throw std::runtime_error("ImageMatrixW::SaveImage() - SetPixel() error occurred");
                            }
                        }
                    }
                    else
                    {
                        bm = new Gdiplus::Bitmap((INT)ib_width, (INT)ib_height, PixelFormat8bppIndexed);

                        if (bm->GetLastStatus() != Gdiplus::Status::Ok)
                            throw std::runtime_error("ImageMatrixW::SaveImage() - bitmap create failed (#2)");

                        void* cp_temp = malloc(sizeof(Gdiplus::ColorPalette) + 255 * sizeof(Gdiplus::ARGB));
                        Gdiplus::ColorPalette* cp = static_cast<Gdiplus::ColorPalette*>(cp_temp);

                        if (cp == NULL)
                            throw std::runtime_error("ImageMatrixW::SaveImage() - ColorPalette allocation error");

                        cp->Count = 256;
                        cp->Flags = Gdiplus::PaletteFlags::PaletteFlagsGrayScale;

                        for (size_t i = 0; i < 256; i++)
                        {
                            BYTE r = (BYTE)i;
                            BYTE g = (BYTE)i;
                            BYTE b = (BYTE)i;
                            Gdiplus::ARGB argb = Gdiplus::Color::MakeARGB(0xff, r, g, b);

                            cp->Entries[i] = argb;
                        }

                        bm->SetPalette(cp);
                        bm->LockBits(&rect, Gdiplus::ImageLockModeWrite, PixelFormat8bppIndexed, &bitmapData);

                        uint8_t* pb_src = ib.GetPixelBuffer<uint8_t>();
                        uint8_t* pb_des = (uint8_t*)bitmapData.Scan0;
                        memcpy(pb_des, pb_src, (size_t)ib_height * ib_width);
                        bm->UnlockBits(&bitmapData);
                        free(cp);
                    }
                }
                else if (ib_pixel_type == PixelType::Rgb32)
                {
                    RGB32* pb_src = ib.GetPixelBuffer<RGB32>();
                    bm = new Gdiplus::Bitmap((INT)ib_width, (INT)ib_height, PixelFormat24bppRGB);

                    if (bm->GetLastStatus() != Gdiplus::Status::Ok)
                        throw std::runtime_error("ImageMatrixW::SaveImage() - bitmap create failed (#3)");

                    for (size_t i = 0; i < ib_height; i++)
                    {
                        for (size_t j = 0; j < ib_width; j++)
                        {
                            RGB32 rgb = *pb_src++;
                            Gdiplus::Color c(0xff, rgb.m_R, rgb.m_G, rgb.m_B);

                            if (bm->SetPixel((INT)j, (INT)i, c) != Gdiplus::Ok)
                                throw std::runtime_error("ImageMatrixW::SaveImage() - SetPixel() error occurred");
                        }
                    }
                }
                else
                    throw std::runtime_error("ImageMatrixW::SaveImage() - unsupported pixel type");

                CLSID pngClsid;
                const wchar_t* format = GetFormatString(file_type);
                GetEncoderClsid(format, &pngClsid);

                std::wstring filename2 = MF::ToWstring(filename);
                status = bm->Save(filename2.c_str(), &pngClsid, NULL);

                if (status != Gdiplus::Ok)
                    throw std::runtime_error("ImageMatrixW::SaveImage() - file save error");
            }

            catch (const std::exception& ex)
            {
                ex_msg = ex.what();
                ex_occurred = true;
            }

            if (bm != nullptr)
                delete bm;

            Gdiplus::GdiplusShutdown(GdiToken);

            if (ex_occurred)
                throw std::runtime_error(ex_msg);
        }
    }
};

#endif // defined(_MSC_VER)
