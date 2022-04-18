//------------------------------------------------
//               Ch11_07_misc.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch11_07.h"

void DisplayResult(const char* s1, int a, int b, int c, int result)
{
    const size_t w = 4;

    std::cout << s1 << "(";
    std::cout << std::setw(w) << a << ", ";
    std::cout << std::setw(w) << b << ", ";
    std::cout << std::setw(w) << c << ") = ";
    std::cout << std::setw(w) << result << '\n';
}
