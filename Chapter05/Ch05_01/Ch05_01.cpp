//------------------------------------------------
//               Ch05_01.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch05_01.h"
#include "AlignedMem.h"

static void CalcLS(void);

int main()
{
    try
    {
        CalcLS();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch05_01 exception: " << ex.what() << '\n';
    }

    return 0;
}

void CalcLS(void)
{
    const size_t n = 59;
    AlignedArray<double> x_aa(n, c_Alignment);
    AlignedArray<double> y_aa(n, c_Alignment);
    double* x = x_aa.Data();
    double* y = y_aa.Data();

    FillArrays(x, y, n);

    double m1, m2;
    double b1, b2;
    CalcLeastSquares_Cpp(&m1, &b1, x, y, n);
    CalcLeastSquares_Iavx2(&m2, &b2, x, y, n);

    size_t w = 12;
    const char nl = '\n';
    std::cout << std::fixed << std::setprecision(8);

    std::cout << "\nCalcLeastSquares_Cpp Results\n";
    std::cout << "  slope:      " << std::setw(w) << m1 << nl;
    std::cout << "  intercept:  " << std::setw(w) << b1 << nl;
    std::cout << "\nCalcLeastSquares_Iavx2 Results\n";
    std::cout << "  slope:      " << std::setw(w) << m2 << nl;
    std::cout << "  intercept:  " << std::setw(w) << b2 << nl;
}
