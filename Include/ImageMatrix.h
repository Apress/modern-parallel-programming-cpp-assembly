//-------------------------------------------------
//               ImageMatrix.h
//-------------------------------------------------

#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cstdint>
#include <cstdlib>
#include <utility>
#include <vector>
#include <random>
#include "MF.h"
#include "ImageMisc.h"
#include "ImageBuffer.h"

#if defined(_MSC_VER)
#include "ImageMatrixW.h"
#elif defined(__GNUG__)
#include "ImageMatrixL.h"
#else
#error Unexpected target in ImageMatrix::ImageMatrix()
#endif

class ImageMatrix
{
    ImageBuffer m_ImageBuffer;

public:
    size_t GetHeight() const                            { return m_ImageBuffer.GetHeight(); }
    size_t GetWidth() const                             { return m_ImageBuffer.GetWidth(); }
    size_t GetNumPixels() const                         { return m_ImageBuffer.GetNumPixels(); }
    size_t GetBytesPerPixel() const                     { return m_ImageBuffer.GetBytesPerPixel(); }
    size_t GetPixelBufferSize() const                   { return m_ImageBuffer.GetPixelBufferSize(); }
    PixelType GetPixelType() const                      { return m_ImageBuffer.GetPixelType(); }
    template <typename T> T* GetPixelBuffer(void) const { return m_ImageBuffer.GetPixelBuffer<T>(); }
    uintptr_t GetPixelBufferUintptr(void) const         { return m_ImageBuffer.GetPixelBufferUintptr(); }

    ImageMatrix(const char* filename, PixelType pixel_type, Channel channel = Channel::None)
    {
        if (pixel_type != PixelType::Gray8 && pixel_type != PixelType::Rgb32)
            throw std::runtime_error("ImageMatrix::LoadImage() - unsupported pixel_type");

#if defined(_MSC_VER)
        ImageMatrixW::LoadImage(m_ImageBuffer, filename, pixel_type, channel);
#endif

#if defined(__GNUG__)
        ImageMatrixL::LoadImage(m_ImageBuffer, filename, pixel_type, channel);
#endif

    }

    ImageMatrix(void)
    {
    }

    ImageMatrix(const ImageMatrix& im) : m_ImageBuffer(im.m_ImageBuffer)
    {
    }

    ImageMatrix(size_t height, size_t width, PixelType pixel_type)
    {
        m_ImageBuffer.Reallocate(height, width, pixel_type);
    }

    ImageMatrix(ImageMatrix&& im) noexcept
    {
        m_ImageBuffer = std::move(im.m_ImageBuffer);
    }

    ~ImageMatrix(void)
    {
    }

    ImageMatrix& operator = (const ImageMatrix& im)
    {
        if (this != &im)
            m_ImageBuffer = im.m_ImageBuffer;

        return *this;
    }

    ImageMatrix& operator = (ImageMatrix&& im) noexcept
    {
        m_ImageBuffer = std::move(im.m_ImageBuffer);
        return *this;
    }

    friend bool operator == (const ImageMatrix& im1, const ImageMatrix& im2)
    {
        if (im1.m_ImageBuffer != im2.m_ImageBuffer)
            return false;

        uint8_t* pb1 = im1.m_ImageBuffer.GetPixelBuffer<uint8_t>();
        uint8_t* pb2 = im2.m_ImageBuffer.GetPixelBuffer<uint8_t>();
        size_t pb_size = im1.m_ImageBuffer.GetPixelBufferSize();

        bool rc = memcmp(pb1, pb2, pb_size) == 0;
        return rc;
    }

    friend bool operator != (const ImageMatrix& im1, const ImageMatrix& im2)
    {
        return !(im1 == im2);
    }

    friend std::ostream& operator << (std::ostream& os, const ImageMatrix& im)
    {
        const char nl = '\n';
        os << "Height:         " << im.GetHeight() << nl;
        os << "Width:          " << im.GetWidth() << nl;
        os << "NumPixels:      " << im.GetNumPixels() << nl;
        os << "BytesPerPixel:  " << im.GetBytesPerPixel() << nl;
        os << "PixelBufferSize " << im.GetPixelBufferSize() << nl;
        os << "PixelType:      " << (unsigned int)im.GetPixelType() << nl;

        std::stringstream ss;
        ss << "0x" << std::setfill('0') << std::hex << std::setw(16) << im.GetPixelBufferUintptr() << nl;

        os << "PixelBuffer:    " << ss.str() << nl;
        return os;
    }

    void SaveImage(const char* filename, ImageFileType file_type)
    {
#if defined(_MSC_VER)
        ImageMatrixW::SaveImage(m_ImageBuffer, filename, file_type);
#endif

#if defined(__GNUG__)
        ImageMatrixL::SaveImage(m_ImageBuffer, filename, file_type);
#endif
    }

    template <typename T> std::vector<T> ToVector(void)
    {
        if (m_ImageBuffer.GetPixelType() != PixelType::Gray8)
            throw std::runtime_error("ImageMatrix::ToVector() - unsupported pixel_type");

        size_t num_pixels = m_ImageBuffer.GetNumPixels();
        const uint8_t* pb_src = m_ImageBuffer.GetPixelBuffer<uint8_t>();
        std::vector<T> v_des(num_pixels);
        T* pb_des = v_des.data();

        for (size_t i = 0; i < num_pixels; i++)
            pb_des[i] = (T)pb_src[i];
    
        return v_des;
    }

    template <typename T> static ImageMatrix ToImage(std::vector<T>& v_src, size_t im_h, size_t im_w, PixelType pixel_type)
    {
        ImageMatrix im(im_h, im_w, pixel_type);
        size_t num_pixels = im.m_ImageBuffer.GetNumPixels();

        if (v_src.size() != num_pixels)
            throw std::runtime_error("ImageMatrix::ToImage() - non-conforming sizes");

        if (pixel_type != PixelType::Gray8)
            throw std::runtime_error("ImageMatrix::ToImage() - invalid pixel_type");

        const T* pb_src = v_src.data();
        uint8_t* pb_des = im.GetPixelBuffer<uint8_t>();

        for (size_t i = 0; i < num_pixels; i++)
            pb_des[i] = (uint8_t)pb_src[i];

        return im;
    }

    template <typename T> void FillBorder(size_t b_size, T val)
    {
        // Temp code - requires error checking and optimization
        size_t im_h = m_ImageBuffer.GetHeight();
        size_t im_w = m_ImageBuffer.GetWidth();
        T* pb = m_ImageBuffer.GetPixelBuffer<T>();

        for (size_t i = 0; i < im_h; i++)
        {
            for (size_t j = 0; j < im_w; j++)
            {
                if ((i < b_size) || ((i + b_size) >= im_h))
                    pb[i * im_w + j] = val;
                else if (j < b_size || ((j + b_size) >= im_w))
                    pb[i * im_w + j] = val;
            }
        }
    }

    template <typename T> void Fill(T val)
    {
        // Temp code - add error checking
        size_t n = m_ImageBuffer.GetNumPixels();
        T* pb = m_ImageBuffer.GetPixelBuffer<T>();

        for (size_t i = 0; i < n; i++)
            pb[i] = val;
    }

    void FillRandom(uint8_t rng_min, uint8_t rng_max, unsigned int rng_seed)
    {
        std::mt19937 rng {rng_seed};
        std::uniform_int_distribution<int> dist {rng_min, rng_max};

        PixelType pixel_type = m_ImageBuffer.GetPixelType();
        size_t num_pixels = m_ImageBuffer.GetNumPixels();

        if (pixel_type == PixelType::Gray8)
        {
            uint8_t* pb = m_ImageBuffer.GetPixelBuffer<uint8_t>();

            for (size_t i = 0; i < num_pixels; i++)
                pb[i] = (uint8_t)dist(rng);
        }
        else if (pixel_type == PixelType::Rgb32)
        {
            RGB32* pb = m_ImageBuffer.GetPixelBuffer<RGB32>();

            for (size_t i = 0; i < num_pixels; i++)
            {
                pb[i].m_R = (uint8_t)dist(rng);
                pb[i].m_G = (uint8_t)dist(rng);
                pb[i].m_B = (uint8_t)dist(rng);
                pb[i].m_A = 0xff;
            }
        }
        else
            throw std::runtime_error("ImageMatrix::FillRandom() - invalid pixel type");
    }

    void AllocRgbArrays(uint8_t** r, uint8_t** g, uint8_t** b, unsigned int alignment)
    {
        if (m_ImageBuffer.GetPixelType() != PixelType::Rgb32)
            throw std::runtime_error("ImageMatrix::AllocRgbArrays() - invalid pixel type");

        size_t num_pixels = m_ImageBuffer.GetNumPixels();

        *r = (uint8_t*)OS::AlignedMalloc(num_pixels * sizeof(uint8_t), alignment);
        *g = (uint8_t*)OS::AlignedMalloc(num_pixels * sizeof(uint8_t), alignment);
        *b = (uint8_t*)OS::AlignedMalloc(num_pixels * sizeof(uint8_t), alignment);
    }

    void FreeRgbArrays(uint8_t* r, uint8_t* g, uint8_t* b)
    {
        if (m_ImageBuffer.GetPixelType() != PixelType::Rgb32)
            throw std::runtime_error("ImageMatrix::FreeRgbArrays() - invalid pixel type");

        OS::AlignedFree(r);
        OS::AlignedFree(g);
        OS::AlignedFree(b);
    }

    void GetRgbPixelData(uint8_t* r, uint8_t* g, uint8_t* b)
    {
        if (m_ImageBuffer.GetPixelType() != PixelType::Rgb32)
            throw std::runtime_error("ImageMatrix::GetRgbPixelData() - invalid pixel type");

        RGB32* pb = m_ImageBuffer.GetPixelBuffer<RGB32>();
        size_t num_pixels = m_ImageBuffer.GetNumPixels();

        for (size_t i = 0; i < num_pixels; i++, pb++)
        {
            *r++ = pb->m_R;
            *g++ = pb->m_G;
            *b++ = pb->m_B;
        }
    }

    void SetRgbPixelData(const uint8_t* r, const uint8_t* g, const uint8_t* b)
    {
        if (m_ImageBuffer.GetPixelType() != PixelType::Rgb32)
            throw std::runtime_error("ImageMatrix::SetRgbPixelData() - invalid pixel type");

        RGB32* pb = m_ImageBuffer.GetPixelBuffer<RGB32>();
        size_t num_pixels = m_ImageBuffer.GetNumPixels();

        for (size_t i = 0; i < num_pixels; i++, pb++)
        {
            pb->m_R = *r++;
            pb->m_G = *g++;
            pb->m_B = *b++;
        }
    }

    static bool AreAlike(const ImageMatrix& im1, const ImageMatrix& im2, uint8_t max_delta, size_t* num_diff)
    {
        *num_diff = 0;

        if (!ImageBuffer::IsConforming(im1.m_ImageBuffer, im2.m_ImageBuffer))
            return false;

        PixelType pixel_type = im1.m_ImageBuffer.GetPixelType();

        if (pixel_type == PixelType::Gray8)
        {
            const uint8_t* pb1 = im1.m_ImageBuffer.GetPixelBuffer<uint8_t>();
            const uint8_t* pb2 = im2.m_ImageBuffer.GetPixelBuffer<uint8_t>();

            // Nested loops used here to simply test & debug
            size_t h = im1.m_ImageBuffer.GetHeight();
            size_t w = im1.m_ImageBuffer.GetWidth();

            for (size_t i = 0; i < h;  i++)
            {
                for (size_t j = 0; j < w;  j++)
                {
                    int pixel1 = (int)pb1[i * w + j];
                    int pixel2 = (int)pb2[i * w + j];

                    if (std::abs(pixel1 - pixel2) > max_delta)
                        *num_diff += 1;
                }
            }

            return (*num_diff) == 0 ? true : false;
        }

        throw std::runtime_error("ImageMatrix::AreAlike() - unsupported pixel type");
    }
};
