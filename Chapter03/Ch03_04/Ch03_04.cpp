//------------------------------------------------
//               Ch03_04.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch03_04.h"
#include "AlignedMem.h"

static void CalcMeanStDevF32(void);

int main()
{
    CalcMeanStDevF32();
    return 0;
}

static void CalcMeanStDevF32(void)
{
    size_t n = c_NumElements;
    AlignedArray<float> x_aa(n, c_Alignment);
    float* x = x_aa.Data();

    InitArray(x, n);

    float mean1, mean2, st_dev1, st_dev2;

    bool rc1 = CalcMeanF32_Cpp(&mean1, x, n);
    bool rc2 = CalcStDevF32_Cpp(&st_dev1, x, n, mean1);
    bool rc3 = CalcMeanF32_Iavx(&mean2, x, n);
    bool rc4 = CalcStDevF32_Iavx(&st_dev2, x, n, mean2);

    if (!rc1 || !rc2 || !rc3 || !rc4)
    {
        std::cout << "Invalid return code\n";
        return;
    }

    unsigned int w = 10;
    const char nl = '\n';
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Results for CalcMeanF32_Cpp and CalcStDevF32_Cpp" << nl;
    std::cout << "mean1:   " << std::setw(w) << mean1 << "  ";
    std::cout << "st_dev1: " << std::setw(w) << st_dev1 << nl << nl;
    std::cout << "Results for CalcMeanF32_Iavx and CalcStDevF32_Iavx" << nl;
    std::cout << "mean2:   " << std::setw(w) << mean2 << "  ";
    std::cout << "st_dev2: " << std::setw(w) << st_dev2 << nl;
}
