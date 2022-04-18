//------------------------------------------------
//               Ch02_06.cpp
//------------------------------------------------

#include <iostream>
#include "Ch02_06.h"
#include "AlignedMem.h"

static void CalcMinMaxU8();

int main()
{
    CalcMinMaxU8();
    CalcMinMaxU8_bm();
}

static void CalcMinMaxU8()
{
    size_t n = c_NumElements;
    AlignedArray<uint8_t> x_aa(n, 16);
    uint8_t* x = x_aa.Data();

    InitArray(x, n, c_RngSeedVal);

    uint8_t x_min1 = 0, x_max1 = 0;
    uint8_t x_min2 = 0, x_max2 = 0;

    bool rc1 = CalcMinMaxU8_Cpp(&x_min1, &x_max1, x, n);
    bool rc2 = CalcMinMaxU8_Iavx(&x_min2, &x_max2, x, n);

    std::cout << "\nResults for CalcMinMaxU8_Cpp\n";
    std::cout << "rc1: " << rc1 << "  x_min1: " << (int)x_min1;
    std::cout << "  x_max1: " << (int)x_max1 << '\n';
    std::cout << "\nResults for CalcMinMaxU8_Iavx\n";
    std::cout << "rc2: " << rc2 << "  x_min2: " << (int)x_min2;
    std::cout << "  x_max2: " << (int)x_max2 << '\n';
}
