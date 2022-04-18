//------------------------------------------------
//               Ch03_05.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch03_05.h"
#include "AlignedMem.h"

static void CalcMeanStDevF64(void);

int main()
{
    CalcMeanStDevF64();
    return 0;
}

static void CalcMeanStDevF64(void)
{
    size_t n = c_NumElements;
    AlignedArray<double> x_aa(n, c_Alignment);
    double* x = x_aa.Data();

    InitArray(x, n);

    double mean1, mean2, st_dev1, st_dev2;

    bool rc1 = CalcMeanF64_Cpp(&mean1, x, n);
    bool rc2 = CalcStDevF64_Cpp(&st_dev1, x, n, mean1);
    bool rc3 = CalcMeanF64_Iavx(&mean2, x, n);
    bool rc4 = CalcStDevF64_Iavx(&st_dev2, x, n, mean2);

    if (!rc1 || !rc2 || !rc3 || !rc4)
    {
        std::cout << "Invalid return code\n";
        return;
    }

    unsigned int w = 10;
    const char nl = '\n';
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Results for CalcMeanF64_Cpp and CalcStDevF64_Cpp" << nl;
    std::cout << "mean1:   " << std::setw(w) << mean1 << "  ";
    std::cout << "st_dev1: " << std::setw(w) << st_dev1 << nl << nl;
    std::cout << "Results for CalcMeanF64_Iavx and CalcStDevF64_Iavx" << nl;
    std::cout << "mean2:   " << std::setw(w) << mean2 << "  ";
    std::cout << "st_dev2: " << std::setw(w) << st_dev2 << nl;
}
