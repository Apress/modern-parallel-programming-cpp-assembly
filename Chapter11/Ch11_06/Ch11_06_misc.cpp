//------------------------------------------------
//               Ch11_06_misc.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch11_06.h"
#include "MT.h"

void FillArray(int* x, size_t n)
{
    const int min_val = -2000;
    const int max_val = 2000;
    const unsigned int rng_seed = 1337;

    MT::FillArray(x, n, min_val, max_val, rng_seed, true);
}

void DisplayResults(const int* x, size_t n, int sum1, int sum2)
{
    const char nl = '\n';
    std::cout << "----- Results for SumElementsI32() -----\n";

    for (size_t i = 0; i < n; i++)
        std::cout << "x[" << i << "] = " << std::setw(4) << x[i] << nl;

    std::cout << nl;
    std::cout << "sum1 = " << sum1 << nl;
    std::cout << "sum2 = " << sum2 << nl;
}
