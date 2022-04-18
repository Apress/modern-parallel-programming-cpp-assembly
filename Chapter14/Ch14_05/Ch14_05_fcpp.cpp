//------------------------------------------------
//               Ch14_05_fcpp.cpp
//------------------------------------------------

#include "Ch14_05.h"

void CalcColumnMeansF64_Cpp(double* col_means, const double* x, size_t nrows,
    size_t ncols)
{
    for (size_t j = 0; j < ncols; j++)
        col_means[j] = 0.0;

    for (size_t i = 0; i < nrows; i++)
    {
        for (size_t j = 0; j < ncols; j++)
            col_means[j] += x[i * ncols + j];
    }

    for (size_t j = 0; j < ncols; j++)
        col_means[j] /= (double)nrows;
}
