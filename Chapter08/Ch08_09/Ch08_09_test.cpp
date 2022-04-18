//------------------------------------------------
//               Ch08_09_test.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include "Ch08_09.h"
#include "MT_Convolve.h"

void DisplayKernel1Dx2(float sigma, size_t ks)
{
    std::vector<float> gk = GenGaussianKernel1D(sigma, ks);

    std::cout << std::fixed << std::setprecision(6);

    float sum = 0.0f;
    for (size_t i = 0; i < ks; i++)
    {
        sum += gk[i];
        std::cout << std::setw(10) << gk[i] << ' ';
    }

    std::cout << '\n';
    std::cout << "  sum = " << sum << "\n\n";
}
