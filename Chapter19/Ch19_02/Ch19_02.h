//------------------------------------------------
//               Ch19_02.h
//------------------------------------------------

#pragma once
#include <array>
#include <vector>

struct CD_1Dx2
{
    size_t m_ImH;
    size_t m_ImW;
    size_t m_KernelSize;
    std::vector<float> m_ImSrc;
    std::vector<float> m_ImDes;
    std::vector<float> m_ImTmp;
    std::vector<float> m_Kernel1Dy;
    std::vector<float> m_Kernel1Dx;
};

enum class KERNEL_ID : unsigned int
{
    LowPass1Dx2_3x3, LowPass1Dx2_5x5, LowPass1Dx2_7x7, LowPass1Dx2_9x9
};

// Ch19_02_fcpp.cpp
extern void Convolve1Dx2_F32_Cpp(CD_1Dx2& cd);
extern void Convolve1Dx2_F32a_Iavx512(CD_1Dx2& cd);

// Ch19_02_fcpp2.cpp
extern void Convolve1Dx2_F32b_Iavx512(CD_1Dx2& cd);

// Ch19_02_misc.cpp
extern bool CheckArgs1Dx2(const CD_1Dx2& cd);
extern void GetKernel1Dx2(CD_1Dx2& cd, KERNEL_ID id);
extern void InitConvData1Dx2(std::array<CD_1Dx2, 3>& cd, const char* fn,
    size_t im_size = 1024);

// Ch19_02_bm.cpp
extern void Convolve1Dx2_F32_bm(void);

// Ch19_02_test.cpp
extern void DisplayKernel1Dx2(float sigma, size_t ks);

// Miscellaneous constants
extern const char* c_TestImageFileName;
