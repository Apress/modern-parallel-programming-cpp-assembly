//------------------------------------------------
//               Ch12_05_fcpp.h
//------------------------------------------------

#include <cmath>
#include "Ch12_05.h"

bool CalcMeanF32_Cpp(float* mean, const float* x, size_t n)
{
    if (n < 2)
        return false;

    float sum = 0.0f;

    for (size_t i = 0; i < n; i++)
        sum += x[i];

    *mean = sum / n;
    return true;
}

bool CalcStDevF32_Cpp(float* st_dev, const float* x, size_t n, float mean)
{
    if (n < 2)
        return false;

    float sum_squares = 0.0f;

    for (size_t i = 0; i < n; i++)
    {
        float temp = x[i] - mean;
        sum_squares += temp * temp;
    }

    *st_dev = sqrt(sum_squares / (n - 1));
    return true;
}
