//------------------------------------------------
//               Ch02_07.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch02_07.h"
#include "AlignedMem.h"

static void CalcMeanU8(void);

int main()
{
    CalcMeanU8();
    CalcMeanU8_bm();
}

static void CalcMeanU8(void)
{
    const char nl = '\n';
    const size_t n = c_NumElements;
    AlignedArray<uint8_t> x_aa(n, 16);
    uint8_t* x = x_aa.Data();

    InitArray(x, n, c_RngSeedVal);

    bool rc0, rc1;
    uint64_t sum_x0, sum_x1;
    double mean_x0, mean_x1;

    rc0 = CalcMeanU8_Cpp(&mean_x0, &sum_x0, x, n);
    rc1 = CalcMeanU8_Iavx(&mean_x1, &sum_x1, x, n);

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "\nResults for CalcMeanU8_Cpp\n";
    std::cout << "rc0: " << rc0 << "  ";
    std::cout << "sum_x0: " << sum_x0 << "  ";
    std::cout << "mean_x0: " << mean_x0 << nl;

    std::cout << "\nResults for CalcMeanU8_Iavx\n";
    std::cout << "rc1: " << rc1 << "  ";
    std::cout << "sum_x1: " << sum_x1 << "  ";
    std::cout << "mean_x1: " << mean_x1 << nl;
}
