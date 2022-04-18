//------------------------------------------------
//               Ch16_05_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include "Ch16_05.h"
#include "MiscTypes.h"

void Convolve1D_F32_Cpp(std::vector<float>& y, const std::vector<float>& x, const std::vector<float>& kernel)
{
    if (!CheckArgs(y, x, kernel))
        throw std::runtime_error("Convolve1D_F32_Cpp() - CheckArgs failed");

    indx_t num_pts = (indx_t)y.size();
    indx_t ks2 = kernel.size() / 2;

    for (indx_t i = ks2; i < num_pts - ks2; i++)
    {
        float y_val = 0;

        for (indx_t k = -ks2; k <= ks2; k++)
            y_val += x[i - k] * kernel[k + ks2];

        y[i] = y_val;
    }
}

