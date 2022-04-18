//------------------------------------------------
//               Ch13_06_misc.cpp
//------------------------------------------------

#include "Ch13_06.h"
#include "MT.h"
#include "AlignedMem.h"

extern size_t g_NumElementsMax = 64 * 1024 * 1024;

bool CheckArgs(const uint8_t* x, size_t n)
{
    if (n == 0 || n > g_NumElementsMax)
        return false;

    if ((n % 64) != 0)
        return false;

    if (!AlignedMem::IsAligned(x, c_Alignment))
        return false;

    return true;
}

void InitArray(uint8_t* x, size_t n, unsigned int rng_seed)
{
    int rng_min_val = 0;
    int rng_max_val = 255;
    MT::FillArray(x, n, rng_min_val, rng_max_val, rng_seed);
}
