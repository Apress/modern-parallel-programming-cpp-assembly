//------------------------------------------------
//               Ch12_07.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Ch12_07.h"

static void CalcSumProd(void);

int main()
{
    CalcSumProd();
    return 0;
}

static void CalcSumProd(void)
{
    const int n = 6;
    const int64_t a[n] = { 2, -2, -6, 7, 12, 5 };
    const int64_t b[n] = { 3, 5, -7, 8, 4, 9 };
    int64_t sum_a, sum_b, prod_a, prod_b;

    CalcSumProd_A(a, b, n, &sum_a, &sum_b, &prod_a, &prod_b);

    const size_t w = 6;
    const char nl = '\n';
    const char* ws = "   ";

    std::cout << "----- Results for CalcSumProd_A -----\n";

    for (int i = 0; i < n; i++)
    {
        std::cout << "i: " << std::setw(w) << i << ws;
        std::cout << "a: " << std::setw(w) << a[i] << ws;
        std::cout << "b: " << std::setw(w) << b[i] << nl;
    }

    std::cout <<  nl;
    std::cout << "sum_a =  " << std::setw(w) << sum_a << ws;
    std::cout << "sum_b =  " << std::setw(w) << sum_b << nl;
    std::cout << "prod_a = " << std::setw(w) << prod_a << ws;
    std::cout << "prod_b = " << std::setw(w) << prod_b << nl;
}
