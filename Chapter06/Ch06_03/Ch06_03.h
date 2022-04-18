//------------------------------------------------
//               Ch06_03.h
//------------------------------------------------

#pragma once
#include <array>
#include <vector>

struct CD_2D
{
    size_t m_ImH = 0;
    size_t m_ImW = 0;
    size_t m_KernelSize = 0;
    std::vector<float> m_ImSrc;
    std::vector<float> m_ImDes;
    std::vector<float> m_Kernel2D;
};

enum class KERNEL_ID : unsigned int
{
    LowPass2D_3x3, LowPass2D_5x5, LowPass2D_7x7, LowPass2D_9x9, LowPass2D_15x15
};

// Ch06_03_fcpp.cpp
extern void Convolve2D_F32_Cpp(CD_2D& cd);
extern void Convolve2D_F32_Iavx2(CD_2D& cd);

// Ch06_03_misc.cpp
extern bool CheckArgs2D(const CD_2D& cd);
extern void Init2D(std::array<CD_2D, 2>& cd, const char* fn, KERNEL_ID id);

// Ch06_03_misc2.cpp
extern void DisplayKernel2D(float sigma, size_t ks);
extern void GetKernel2D(CD_2D& cd, KERNEL_ID id);

// Ch06_03_bm.cpp
extern void Convolve2D_F32_bm(void);

// Miscellaneous constants
const KERNEL_ID c_KernelID = KERNEL_ID::LowPass2D_15x15;
const KERNEL_ID c_KernelID_BM = KERNEL_ID::LowPass2D_9x9;
