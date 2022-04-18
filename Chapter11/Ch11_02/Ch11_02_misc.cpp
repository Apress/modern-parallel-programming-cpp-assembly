//------------------------------------------------
//               Ch11_02_misc.cpp
//------------------------------------------------

#include <iostream>
#include "Ch11_02.h"

void DisplayResultsMulI32(int32_t a, int32_t b, int32_t c, int32_t d)
{
    const char nl = '\n';
    std::cout << "Results for MulI32_A()\n";
    std::cout << "a = " << a << nl;
    std::cout << "b = " << b << nl;
    std::cout << "c = " << c << nl;
    std::cout << "d = " << d << nl;
    std::cout << nl;
}

void DisplayResultsMulU64(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    const char nl = '\n';
    std::cout << "Results for MulU64_A()\n";
    std::cout << "a = " << a << nl;
    std::cout << "b = " << b << nl;
    std::cout << "c = " << c << nl;
    std::cout << "d = " << d << nl;
    std::cout << nl;
}
