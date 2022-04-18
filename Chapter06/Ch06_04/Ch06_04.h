//------------------------------------------------
//               Ch06_04.h
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
    std::vector<float> m_Kernel1Dx;
    std::vector<float> m_Kernel1Dy;
};

enum class KERNEL_ID : unsigned int
{
    LowPass1Dx2_3x3, LowPass1Dx2_5x5, LowPass1Dx2_7x7,
    LowPass1Dx2_9x9, LowPass1Dx2_15x15
};

// Ch06_04_fcpp.cpp
extern void Convolve1Dx2_F32_Cpp(CD_1Dx2& cd);
extern void Convolve1Dx2_F32_Iavx2(CD_1Dx2& cd);

// Ch06_04_misc.cpp
extern bool CheckArgs1Dx2(const CD_1Dx2& cd);
extern void Init1Dx2(std::array<CD_1Dx2, 2>& cd, const char* fn, KERNEL_ID id);

// Ch06_04_misc2.cpp
extern void DisplayKernel1Dx2(float sigma, size_t ks);
extern void GetKernel1Dx2(CD_1Dx2& cd, KERNEL_ID id);

// Ch06_04_bm.cpp
extern void Convolve1Dx2_F32_bm(void);

// Miscellaneous constants
const KERNEL_ID c_KernelID = KERNEL_ID::LowPass1Dx2_15x15;
const KERNEL_ID c_KernelID_BM = KERNEL_ID::LowPass1Dx2_9x9;
