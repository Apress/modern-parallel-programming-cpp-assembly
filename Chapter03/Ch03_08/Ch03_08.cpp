//------------------------------------------------
//               Ch03_08.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch03_08.h"
#include "MT.h"

static void CalcColumnMeansF32(void);

int main()
{
    CalcColumnMeansF32();
    return 0;
}

static void CalcColumnMeansF32(void)
{
    const char nl = '\n';
    const size_t nrows = 21;
    const size_t ncols = 15;
    MatrixF32 x(nrows, ncols);
    float* x_data = x.Data();

    MT::FillMatrixFP(x_data, nrows, ncols, c_MatrixFillMin, c_MatrixFillMax, c_RngSeed);

    std::vector<float> col_means1 = CalcColumnMeansF32_Cpp(x);
    std::vector<float> col_means2 = CalcColumnMeansF32_Iavx(x);

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

    if (!MT::CompareVectorsFP(col_means1, col_means2, 1.0e-6f))
        std::cout << "MT::CompareVectorsFP() failed\n";
}
