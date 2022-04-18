//------------------------------------------------
//               Ch08_09.h
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

// Ch08_09_fcpp.cpp
extern void Convolve1Dx2_F32_Cpp(CD_1Dx2& cd);
extern void Convolve1Dx2_F32_Iavx512(CD_1Dx2& cd);

// Ch08_09_misc.cpp
extern bool CheckArgs1Dx2(const CD_1Dx2& cd);
extern void GetKernel1Dx2(CD_1Dx2& cd, KERNEL_ID id);
extern void InitConvData1Dx2(std::array<CD_1Dx2, 2>& cd, const char* fn);

// Ch08_09_bm.cpp
extern void Convolve1Dx2_F32_bm(void);

// Ch08_09_test.cpp
extern void DisplayKernel1Dx2(float sigma, size_t ks);
