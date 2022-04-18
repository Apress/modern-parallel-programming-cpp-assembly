//------------------------------------------------
//               Ch11_05.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Ch11_05.h"

static void MemAddressing(void);

int main()
{
    MemAddressing();
    return 0;
}

static void MemAddressing()
{
    const int w = 5;
    const char nl = '\n';
    const char* delim = ", ";

    int n = g_NumPrimes_A;

    g_SumPrimes_A = 0;

    for (int i = -1; i < n + 1; i++)
    {
        int v1 = -1, v2 = -1, v3 = -1, v4 = -1;
        int rc = MemAddressing_A(i, &v1, &v2, &v3, &v4);

        std::cout << "i = " << std::setw(w - 1) << i << delim;
        std::cout << "rc = " << std::setw(w - 1) << rc << delim;
        std::cout << "v1 = " << std::setw(w) << v1 << delim;
        std::cout << "v2 = " << std::setw(w) << v2 << delim;
        std::cout << "v3 = " << std::setw(w) << v3 << delim;
        std::cout << "v4 = " << std::setw(w) << v4 << delim;
        std::cout << nl;
    }

    std::cout << "\ng_SumPrimes_A = " << g_SumPrimes_A << nl;
}
