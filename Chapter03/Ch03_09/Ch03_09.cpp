//------------------------------------------------
//               Ch03_09.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch03_09.h"
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
    MatrixF64 x(nrows, ncols);
    double* x_data = x.Data();

    MT::FillMatrixFP(x_data, nrows, ncols, c_MatrixFillMin, c_MatrixFillMax, c_RngSeed);

    std::vector<double> col_means1 = CalcColumnMeansF64_Cpp(x);
    std::vector<double> col_means2 = CalcColumnMeansF64_Iavx(x);

    size_t w = 5;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "----- Test Matrix -----\n";

    for (size_t i = 0; i < nrows; i++)
    {
        for (size_t j = 0; j < ncols; j++)
            std::cout << std::setw(w) << x_data[i * ncols + j] << " ";
        std::cout << nl;
    }

    std::cout << "\n----- Column Means -----\n";

    for (size_t j = 0; j < ncols; j++)
        std::cout << std::setw(w) << col_means1[j] << " ";
    std::cout << nl;
    for (size_t j = 0; j < ncols; j++)
        std::cout << std::setw(w) << col_means2[j] << " ";
    std::cout << nl;

    if (!MT::CompareVectorsFP(col_means1, col_means2, 1.0e-6))
        std::cout << "MT::CompareVectorsFP() failed\n";
}
