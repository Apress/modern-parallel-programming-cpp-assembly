//------------------------------------------------
//               Ch12_05.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch12_05.h"
#include "MT.h"

static void CalcMeanStDevF32(void);

int main()
{
    CalcMeanStDevF32();
    return 0;
}

static void CalcMeanStDevF32(void)
{
    const size_t n = c_NumElements;
    std::vector<float> x_v(c_NumElements);
    float* x = x_v.data();

    MT::FillArrayFP(x, n, c_ArrayFillMin, c_ArrayFillMax, c_RngSeed);

    float mean1, mean2, st_dev1, st_dev2;

    bool rc1 = CalcMeanF32_Cpp(&mean1, x, n);
    bool rc2 = CalcMeanF32_Aavx(&mean2, x, n);
    bool rc3 = CalcStDevF32_Cpp(&st_dev1, x, n, mean1);
    bool rc4 = CalcStDevF32_Aavx(&st_dev2, x, n, mean2);

    if (!rc1 || !rc2 || !rc3 || !rc4)
    {
        std::cout << "Invalid return code\n";
        return;
    }

    const char nl = '\n';
    unsigned int w = 10;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Results for CalcMeanF32_Cpp and CalcStDevF32_Cpp" << nl;
    std::cout << "mean1:   " << std::setw(w) << mean1 << "  ";
    std::cout << "st_dev1: " << std::setw(w) << st_dev1 << nl << nl;
    std::cout << "Results for CalcMeanF32_Aavx and CalcStDevF32_Aavx" << nl;
    std::cout << "mean2:   " << std::setw(w) << mean2 << "  ";
    std::cout << "st_dev2: " << std::setw(w) << st_dev2 << nl;
}
