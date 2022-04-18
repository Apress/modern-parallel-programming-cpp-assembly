//------------------------------------------------
//               Ch14_05.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include "Ch14_05.h"
#include "MatrixF64.h"
#include "MT.h"

static void CalcColumnMeansF64(void);

int main()
{
    CalcColumnMeansF64();
    return 0;
}

static void CalcColumnMeansF64(void)
{
    const char nl = '\n';
    const size_t nrows = 21;
    const size_t ncols = 15;
    MatrixF64 x_m(nrows, ncols);
    std::vector<double> col_means1(ncols);
    std::vector<double> col_means2(ncols);
    double* x = x_m.Data();

    MT::FillMatrixFP(x, nrows, ncols, c_MatrixFillMin, c_MatrixFillMax, c_RngSeed);

    CalcColumnMeansF64_Cpp(col_means1.data(), x, nrows, ncols);
    CalcColumnMeansF64_Aavx(col_means2.data(), x, nrows, ncols);

    size_t w = 5;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Results for CalcColumnMeansF64\n";

    for (size_t i = 0; i < nrows; i++)
    {
        for (size_t j = 0; j < ncols; j++)
            std::cout << std::setw(w) << x[i * ncols + j] << " ";
        std::cout << nl;
    }

    std::cout << nl;

    for (size_t j = 0; j < ncols; j++)
        std::cout << std::setw(w) << col_means1[j] << " ";
    std::cout << nl;

    for (size_t j = 0; j < ncols; j++)
        std::cout << std::setw(w) << col_means2[j] << " ";
    std::cout << nl;

    if (!MT::CompareVectorsFP(col_means1, col_means2, 1.0e-6))
        std::cout << "MT::CompareVectorsFP() failed\n";
}
