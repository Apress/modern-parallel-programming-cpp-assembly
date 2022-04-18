//------------------------------------------------
//               Ch11_01_misc.cpp
//------------------------------------------------

#include <iostream>
#include "Ch11_01.h"

void DisplayResultsAddI32(int a, int b, int c, int d)
{
    const char nl = '\n';
    std::cout << "Results for AddI32_A()\n";
    std::cout << "a = " << a << nl;
    std::cout << "b = " << b << nl;
    std::cout << "c = " << c << nl;
    std::cout << "d = " << d << nl;
    std::cout << nl;
}

void DisplayResultsSubI64(long long a, long long b, long long c, long long d)
{
    const char nl = '\n';
    std::cout << "Results for SubI64_A()\n";
    std::cout << "a = " << a << nl;
    std::cout << "b = " << b << nl;
    std::cout << "c = " << c << nl;
    std::cout << "d = " << d << nl;
    std::cout << nl;
}
