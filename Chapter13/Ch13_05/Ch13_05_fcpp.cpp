//------------------------------------------------
//               Ch13_05_fcpp.cpp
//------------------------------------------------

#include "Ch13_05.h"
#include "AlignedMem.h"

bool CalcMinMaxU8_Cpp(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, size_t n)
{
    if (n == 0 || (n & 0xf) != 0)
        return false;

    if (!AlignedMem::IsAligned(x, 16))
        return false;

    uint8_t min_val = 0xff;
    uint8_t max_val = 0;

    for (size_t i = 0; i < n; i++)
    {
        uint8_t val = *x++;

        if (val < min_val)
            min_val = val;
        else if (val > max_val)
            max_val = val;
    }

    *x_min = min_val;
    *x_max = max_val;
    return true;
}
