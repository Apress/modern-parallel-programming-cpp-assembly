//------------------------------------------------
//               Ch03_09_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch03_09.h"

std::vector<double> CalcColumnMeansF64_Cpp(const MatrixF64& x)
{
    size_t nrows = x.GetNumRows();
    size_t ncols = x.GetNumCols();
    const double* x_data = x.Data();
    std::vector<double> col_means(ncols, 0.0);

    for (size_t i = 0; i < nrows; i++)
    {
        for (size_t j = 0; j < ncols; j++)
            col_means[j] += x_data[i * ncols + j];
    }

    for (size_t j = 0; j < ncols; j++)
        col_means[j] /= (double)nrows;
    return col_means;
}

std::vector<double> CalcColumnMeansF64_Iavx(const MatrixF64& x)
{
    size_t nrows = x.GetNumRows();
    size_t ncols = x.GetNumCols();
    const double* x_data = x.Data();
    std::vector<double> col_means(ncols, 0.0);
    double* cm = col_means.data();

    const size_t num_simd_elements = 4;
    const size_t num_simd_elements2 = 2;

    for (size_t i = 0; i < nrows; i++)
    {
        size_t j = 0;

        while (j < ncols)
        {
            if (j + num_simd_elements <= ncols)
            {
                __m256d x_vals = _mm256_loadu_pd(&x_data[i * ncols + j]);
                __m256d cm_vals = _mm256_loadu_pd(&cm[j]);

                cm_vals = _mm256_add_pd(cm_vals, x_vals);
                _mm256_storeu_pd(&cm[j], cm_vals);

                j += num_simd_elements;
            }
            else if (j + num_simd_elements2 <= ncols)
            {
                __m128d x_vals = _mm_loadu_pd(&x_data[i * ncols + j]);
                __m128d cm_vals = _mm_loadu_pd(&cm[j]);

                cm_vals = _mm_add_pd(cm_vals, x_vals);
                _mm_storeu_pd(&cm[j], cm_vals);

                j += num_simd_elements2;
            }
            else
            {
                cm[j] += x_data[i * ncols + j];
                j += 1;
            }
        }
    }

    for (size_t j = 0; j < ncols; j++)
        col_means[j] /= (float)nrows;
    return col_means;
}
