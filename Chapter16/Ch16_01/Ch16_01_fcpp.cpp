//------------------------------------------------
//               Ch16_01_fcpp.cpp
//------------------------------------------------

#include <cmath>
#include <stdexcept>
#include "Ch16_01.h"

void CalcLeastSquares_Cpp(double* m, double* b, const double* x, const double* y, size_t n)
{
    *m = 0.0;
    *b = 0.0;

    if (!CheckArgs(x, y, n))
        throw std::runtime_error("CalcLeastSquares_cpp() CheckArgs failed");

    double sum_x = 0.0, sum_y = 0.0, sum_xx = 0.0, sum_xy = 0.0;

    for (size_t i = 0; i < n; i++)
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_xx += x[i] * x[i];
        sum_xy += x[i] * y[i];
    }

    double denom = n * sum_xx - sum_x * sum_x;

    if (fabs(denom) >= c_LsEpsilon)
    {
        *m = (n * sum_xy - sum_x * sum_y) / denom;
        *b = (sum_xx * sum_y - sum_x * sum_xy) / denom;
    }
}
