//------------------------------------------------
//               Ch13_05.cpp
//------------------------------------------------

#include <iostream>
#include "Ch13_05.h"
#include "AlignedMem.h"

static void CalcMinMaxU8();

int main()
{
    CalcMinMaxU8();
    CalcMinMaxU8_bm();
}

static void CalcMinMaxU8()
{
    const char nl = '\n';
    size_t n = c_NumElements;
    AlignedArray<uint8_t> x_aa(n, 16);
    uint8_t* x = x_aa.Data();

    InitArray(x, n, c_RngSeedVal);

    uint8_t x_min0 = 0, x_max0 = 0;
    uint8_t x_min1 = 0, x_max1 = 0;

    bool rc0 = CalcMinMaxU8_Cpp(&x_min0, &x_max0, x, n);
    bool rc1 = CalcMinMaxU8_Aavx(&x_min1, &x_max1, x, n);

    std::cout << "\nResults for CalcMinMaxU8_Cpp\n";
    std::cout << "rc0: " << rc0 << "  x_min0: " << (int)x_min0;
    std::cout << "  x_max0: " << (int)x_max0 << nl;

    std::cout << "\nResults for CalcMinMaxU8_Aavx\n";
    std::cout << "rc1: " << rc1 << "  x_min1: " << (int)x_min1;
    std::cout << "  x_max1: " << (int)x_max1 << nl;
}
