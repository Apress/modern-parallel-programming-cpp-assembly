//------------------------------------------------
//               Ch12_02_misc.cpp
//------------------------------------------------

#include "Ch12_02.h"
#include "MT.h"

void InitArrays(double* x, double* y, double* z, size_t n, unsigned int rng_seed)
{
    const int rng_min = 1;
    const int rng_max = 99;

    MT::FillArray(x, n, rng_min, rng_max, rng_seed);
    MT::FillArray(y, n, rng_min, rng_max, rng_seed + 1);
    MT::FillArray(z, n, rng_min, rng_max, rng_seed + 2);
}
