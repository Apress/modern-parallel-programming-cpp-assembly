//------------------------------------------------
//               Ch16_01_misc.cpp
//------------------------------------------------

#include <cmath>
#include "Ch16_01.h"
#include "AlignedMem.h"
#include "MT.h"

extern "C" double g_LsEpsilon = c_LsEpsilon;

bool CheckArgs(const double* x, const double* y, size_t n)
{
    if (n < 2)
        return false;

    if (!AlignedMem::IsAligned(x, c_Alignment))
        return false;

    if (!AlignedMem::IsAligned(y, c_Alignment))
        return false;

    return true;
}

void FillArrays(double* x, double* y, size_t n)
{
    const unsigned int rng_seed1 = 73;
    const unsigned int rng_seed2 = 83;
    const double fill_min_val = -25.0;
    const double fill_max_val = 25.0;

    MT::FillArrayFP(x, n, fill_min_val, fill_max_val, rng_seed1);
    MT::FillArrayFP(y, n, fill_min_val, fill_max_val, rng_seed2);

    for (size_t i = 0; i < n; i++)
        y[i] = y[i] * y[i];
}
