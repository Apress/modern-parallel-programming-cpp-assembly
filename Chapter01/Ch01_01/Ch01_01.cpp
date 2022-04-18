//------------------------------------------------
//               Ch01_01.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include "Ch01_01.h"

int main()
{
    const size_t n = 19;
    float x[n], y[n], z1[n], z2[n], z3[n];

    // Initialize the data arrays
    for (size_t i = 0; i < n; i++)
    {
        x[i] = i * 10.0f + 10.0f;
        y[i] = i * 1000.0f + 1000.0f;
        z1[i] = z2[i] = z3[i] = 0.0f;
    }

    // Exercise the SIMD calculating functions
    CalcZ_Cpp(z1, x, y, n);
    CalcZ_Iavx(z2, x, y, n);
    CalcZ_Aavx(z3, x, y, n);

    // Display the results
    const char nl = '\n';
    const size_t w = 10;
    std::cout << std::fixed << std::setprecision(1);

    std::cout << std::setw(w) << "i";
    std::cout << std::setw(w) << "x";
    std::cout << std::setw(w) << "y";
    std::cout << std::setw(w) << "z1";
    std::cout << std::setw(w) << "z2";
    std::cout << std::setw(w) << "z3" << nl;
    std::cout << std::string(60, '-') << nl;

    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::setw(w) << i;
        std::cout << std::setw(w) << x[i];
        std::cout << std::setw(w) << y[i];
        std::cout << std::setw(w) << z1[i];
        std::cout << std::setw(w) << z2[i];
        std::cout << std::setw(w) << z3[i] << nl;
    }
}
