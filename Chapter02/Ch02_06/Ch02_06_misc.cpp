//------------------------------------------------
//               Ch02_06_misc.cpp
//------------------------------------------------

#include "Ch02_06.h"
#include "MT.h"

void InitArray(uint8_t* x, size_t n, unsigned int rng_seed)
{
    int rng_min_val = 5;
    int rng_max_val = 250;
    MT::FillArray(x, n, rng_min_val, rng_max_val, rng_seed);

    // Use known values for min & max (for test purposes)
    x[(n / 4) * 3 + 1] = 2;
    x[n / 4 + 11] = 3;
    x[n / 2] = 252;
    x[n / 2 + 13] = 253;
    x[n / 8 + 5] = 4;
    x[n / 8 + 7] = 254;
}
