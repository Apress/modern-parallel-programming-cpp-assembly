//------------------------------------------------
//               Ch19_01_fcpp2.cpp
//------------------------------------------------

#include <stdexcept>
#include "Ch19_01.h"
#include "MatrixF32.h"

void CalcRowStatsF32_Cpp(MatrixF32& x, std::vector<float>& row_means,
    std::vector<float>& row_sds)
{
    if (!CheckArgs(x, row_means, row_sds))
        throw std::runtime_error("CalcRowStatsF32_Cpp() - CheckArgs failed");

    size_t nrows = x.GetNumRows();
    size_t ncols = x.GetNumCols();
    const float* xx = x.Data();

    for (size_t i = 0; i < nrows; i++)
    {
        float sum = 0.0f;

        for (size_t j = 0; j < ncols; j++)
            sum += xx[i * ncols + j];
        row_means[i] = sum / ncols;

        float sum_sqs = 0.0f;

        for (size_t j = 0; j < ncols; j++)
        {
            float temp = xx[i * ncols + j] - row_means[i];
            sum_sqs += temp * temp;
        }
        row_sds[i] =  sqrt(sum_sqs / (ncols - 1));
    }
}
