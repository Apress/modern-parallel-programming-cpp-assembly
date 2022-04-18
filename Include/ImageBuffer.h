//------------------------------------------------
//               ImageBuffer.h
//------------------------------------------------

#pragma once
#include <cstdlib>
#include <cstdint>
#include <stdexcept>
#include "OS.h"
#include "ImageMisc.h"

class ImageBuffer
{
    static const size_t c_PixelBufferAlignment = 64;

    size_t m_Height = 0;
    size_t m_Width = 0;
    size_t m_BytesPerPixel = 0;
    size_t m_PixelBufferSize = 0;
    void* m_PixelBuffer = nullptr;
    PixelType m_PixelType = PixelType::Undefined;

    void Allocate(size_t height, size_t width, PixelType pixel_type)
    {
        if (m_PixelBuffer != nullptr)
            throw std::runtime_error("ImageBuffer::Allocate() - invalid value (m_PixelBuffer)");

        if (pixel_type == PixelType::Gray8)
            m_BytesPerPixel = 1;
        else if (pixel_type == PixelType::Rgb32)
            m_BytesPerPixel = sizeof(RGB32);
        else
            throw std::runtime_error("ImageBuffer::Allocate() - invalid value (pixel_type)");

        m_Height = height;
        m_Width = width;
        m_PixelBufferSize = m_Height * m_Width * m_BytesPerPixel;
        m_PixelType = pixel_type;
        m_PixelBuffer = OS::AlignedMalloc(m_PixelBufferSize, c_PixelBufferAlignment);
    };

    void Cleanup(void)
    {
        m_Height = 0;
        m_Width = 0;
        m_BytesPerPixel = 0;
        m_PixelBufferSize = 0;
        m_PixelBuffer = nullptr;
        m_PixelType = PixelType::Undefined;
    }

    bool IsConforming(size_t height, size_t width, PixelType pixel_type)
    {
        return m_Height == height && m_Width == width && m_PixelType == pixel_type;
    }

    void Release(void)
    {
        if (m_PixelBuffer != nullptr)
            OS::AlignedFree(m_PixelBuffer);

        Cleanup();
    }

public:
    size_t GetHeight() const                            { return m_Height; }
    size_t GetWidth() const                             { return m_Width; }
    size_t GetNumPixels() const                         { return m_Height * m_Width; }
    size_t GetBytesPerPixel() const                     { return m_BytesPerPixel; }
    size_t GetPixelBufferSize() const                   { return m_PixelBufferSize; }
    PixelType GetPixelType() const                      { return m_PixelType; }
    template <typename T> T* GetPixelBuffer(void) const { return (T*)m_PixelBuffer; }
    uintptr_t GetPixelBufferUintptr(void) const         { return (uintptr_t)m_PixelBuffer; }

    ImageBuffer(void)
    {
    }

    ImageBuffer(size_t height, size_t width, PixelType pixel_type)
    {
        Allocate(height, width, pixel_type);
    }

    ImageBuffer(const ImageBuffer& ib)
    {
        Allocate(ib.m_Height, ib.m_Width, ib.m_PixelType);
        memcpy(m_PixelBuffer, ib.m_PixelBuffer, m_PixelBufferSize);
    }

    ImageBuffer(ImageBuffer&& ib) noexcept : m_Height(ib.m_Height), m_Width(ib.m_Width),
                                         m_BytesPerPixel(ib.m_BytesPerPixel), m_PixelBufferSize(ib.m_PixelBufferSize),
                                         m_PixelBuffer(ib.m_PixelBuffer), m_PixelType(ib.m_PixelType)
    {
        ib.Cleanup();
    }

    ImageBuffer& operator = (const ImageBuffer& ib)
    {
        if (this != &ib)
        {
            if (!IsConforming(*this, ib))
            {
                Release();
                Allocate(ib.m_Height, ib.m_Width, ib.m_PixelType);
            }

            memcpy(m_PixelBuffer, ib.m_PixelBuffer, m_PixelBufferSize);
        }

        return *this;
    }

    ImageBuffer& operator = (ImageBuffer&& ib) noexcept
    {
        Release();

        m_Height = ib.m_Height;
        m_Width = ib.m_Width;
        m_BytesPerPixel = ib.m_BytesPerPixel;
        m_PixelBufferSize = ib.m_PixelBufferSize;
        m_PixelBuffer = ib.m_PixelBuffer;
        m_PixelType = ib.m_PixelType;

        ib.Cleanup();
        return *this;
    }

    ~ImageBuffer()
    {
        Release();
    }

    friend bool operator == (const ImageBuffer& ib1, const ImageBuffer& ib2)
    {
        if (ib1.m_Height != ib2.m_Height)
            return false;
        if (ib1.m_Width != ib2.m_Width)
            return false;
        if (ib1.m_BytesPerPixel != ib2.m_BytesPerPixel)
            return false;
        if (ib1.m_PixelBufferSize != ib2.m_PixelBufferSize)
            return false;
        if (ib1.m_PixelType != ib2.m_PixelType)
            return false;

        return true;
    }

    friend bool operator != (const ImageBuffer& ib1, const ImageBuffer& ib2)
    {
        return !(ib1 == ib2);
    }

    static bool IsConforming(const ImageBuffer& ib1, const ImageBuffer& ib2)
    {
        return ib1.m_PixelType == ib2.m_PixelType && ib1.m_Height == ib2.m_Height && ib1.m_Width == ib2.m_Width;
    }

    void Reallocate(size_t height, size_t width, PixelType pixel_type)
    {
        if (!IsConforming(height, width, pixel_type))
        {
            Release();
            Allocate(height, width, pixel_type);
        }
    }
};
