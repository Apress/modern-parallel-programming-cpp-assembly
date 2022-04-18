//------------------------------------------------
//               Ch03_08_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch03_08.h"

std::vector<float> CalcColumnMeansF32_Cpp(const MatrixF32& x)
{
    size_t nrows = x.GetNumRows();
    size_t ncols = x.GetNumCols();
    const float* x_data = x.Data();
    std::vector<float> col_means(ncols, 0.0f);

    for (size_t i = 0; i < nrows; i++)
    {
        for (size_t j = 0; j < ncols; j++)
            col_means[j] += x_data[i * ncols + j];
    }

    for (size_t j = 0; j < ncols; j++)
        col_means[j] /= (float)nrows;
    return col_means;
}

std::vector<float> CalcColumnMeansF32_Iavx(const MatrixF32& x)
{
    size_t nrows = x.GetNumRows();
    size_t ncols = x.GetNumCols();
    const float* x_data = x.Data();
    std::vector<float> col_means(ncols, 0.0f);
    float* cm = col_means.data();

    const size_t num_simd_elements = 8;
    const size_t num_simd_elements2 = 4;

    for (size_t i = 0; i < nrows; i++)
    {
        size_t j = 0;

        while (j < ncols)
        {
            if (j + num_simd_elements <= ncols)
            {
                __m256 x_vals = _mm256_loadu_ps(&x_data[i * ncols + j]);
                __m256 cm_vals = _mm256_loadu_ps(&cm[j]);

                cm_vals = _mm256_add_ps(cm_vals, x_vals);
                _mm256_storeu_ps(&cm[j], cm_vals);

                j += num_simd_elements;
            }
            else if (j + num_simd_elements2 <= ncols)
            {
                __m128 x_vals = _mm_loadu_ps(&x_data[i * ncols + j]);
                __m128 cm_vals = _mm_loadu_ps(&cm[j]);

                cm_vals = _mm_add_ps(cm_vals, x_vals);
                _mm_storeu_ps(&cm[j], cm_vals);

                j += num_simd_elements2;
            }
            else
            {
                for (; j < ncols; j++)
                    cm[j] += x_data[i * ncols + j];
            }
        }
    }

    for (size_t j = 0; j < ncols; j++)
        col_means[j] /= (float)nrows;
    return col_means;
}
