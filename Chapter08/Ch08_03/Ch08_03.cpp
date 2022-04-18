//------------------------------------------------
//               Ch08_03.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch08_03.h"
#include "AlignedMem.h"
#include "MT.h"

static void CalcMeanStDevF32(void);

int main()
{
    try
    {
        CalcMeanStDevF32();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch08_03 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void CalcMeanStDevF32(void)
{
    size_t n = c_NumElements;
    AlignedArray<float> x_aa(n, c_Alignment);
    float* x = x_aa.Data();

    InitArray(x, n);

    float mean1, mean2, st_dev1, st_dev2;

    CalcMeanF32_Cpp(&mean1, x, n);
    CalcMeanF32_Iavx512(&mean2, x, n);
    CalcStDevF32_Cpp(&st_dev1, x, n, mean1);
    CalcStDevF32_Iavx512(&st_dev2, x, n, mean2);

    unsigned int w = 10;
    const char nl = '\n';
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Results for CalcMeanF32_Cpp and CalcStDevF32_Cpp" << nl;
    std::cout << "mean1:   " << std::setw(w) << mean1 << "  ";
    std::cout << "st_dev1: " << std::setw(w) << st_dev1 << nl << nl;
    std::cout << "Results for CalcMeanF32_Iavx512 and CalcStDevF32_Iavx512" << nl;
    std::cout << "mean2:   " << std::setw(w) << mean2 << "  ";
    std::cout << "st_dev2: " << std::setw(w) << st_dev2 << nl;
}
