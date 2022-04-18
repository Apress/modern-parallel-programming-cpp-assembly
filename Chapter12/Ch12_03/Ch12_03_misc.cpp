//------------------------------------------------
//               Ch12_03_misc.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch12_03.h"

static const char* c_OpStrings[c_NumCmpOps] =
    { "UO", "LT", "LE", "EQ", "NE", "GT", "GE" };

void DisplayResults(float a, float b, const uint8_t* cmp_results)
{
    std::cout << "a = " << a << ", ";
    std::cout << "b = " << b << '\n';

    for (size_t i = 0; i < c_NumCmpOps; i++)
    {
        std::cout << c_OpStrings[i] << '=';
        std::cout << std::boolalpha << std::left;
        std::cout << std::setw(6) << (int)cmp_results[i] << ' ';
    }

    std::cout << "\n\n";
}
