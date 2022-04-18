//------------------------------------------------
//               Ch09_03.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Ch09_03.h"

static void CalcBSA(void);

int main()
{
    try
    {
        CalcBSA();
        CalcBSA_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch09_03 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void CalcBSA(void)
{
    const size_t n = 19;
    std::vector<double> heights(n);
    std::vector<double> weights(n);
    std::vector<double> bsa1(n * 3);
    std::vector<double> bsa2(n * 3);

    FillHeightWeightVectors(heights, weights);

    CalcBSA_F64_Cpp(bsa1, heights, weights);
    CalcBSA_F64_Iavx(bsa2, heights, weights);

    size_t w = 8;
    std::cout << std::fixed;
    std::cout << "----- Results for CalcBSA -----\n\n";

    std::cout << "        ht(cm)    wt(kg)";
    std::cout << "    CppAlg0   CppAlg1   CppAlg2";
    std::cout << "    AvxAlg0   AvxAlg1   AvxAlg2";
    std::cout << '\n' << std::string(86, '-') << '\n';

    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::setw(4) << i << ": ";

        std::cout << std::setprecision(2);
        std::cout << std::setw(w) << heights[i] << "  ";
        std::cout << std::setw(w) << weights[i] << " | ";

        std::cout << std::setprecision(4);
        std::cout << std::setw(w) << bsa1[(n * 0) + i] << "  ";
        std::cout << std::setw(w) << bsa1[(n * 1) + i] << "  ";
        std::cout << std::setw(w) << bsa1[(n * 2) + i] << " | ";
        std::cout << std::setw(w) << bsa2[(n * 0) + i] << "  ";
        std::cout << std::setw(w) << bsa2[(n * 1) + i] << "  ";
        std::cout << std::setw(w) << bsa2[(n * 2) + i] << '\n';
    }

    if (!CompareResults(bsa1, bsa2))
        throw std::runtime_error("CompareResults() failed");
}
