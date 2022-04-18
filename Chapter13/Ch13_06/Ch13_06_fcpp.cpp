//------------------------------------------------
//               Ch13_06_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch13_06.h"

bool CalcMeanU8_Cpp(double* mean_x, uint64_t* sum_x, const uint8_t* x, size_t n)
{
    if (!CheckArgs(x, n))
        return false;

    uint64_t sum_x_temp = 0;

    for (size_t i = 0; i < n; i++)
        sum_x_temp += x[i];

    *sum_x = sum_x_temp;
    *mean_x = (double)sum_x_temp / n;
    return true;
}
