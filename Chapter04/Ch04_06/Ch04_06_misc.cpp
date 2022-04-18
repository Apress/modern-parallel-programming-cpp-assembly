//------------------------------------------------
//               Ch04_06_misc.cpp
//------------------------------------------------

#include "Ch04_06.h"
#include "AlignedMem.h"

bool CheckArgs(size_t num_pixels, const uint8_t* pb_src, const uint8_t* pb_mask)
{
    if ((num_pixels == 0) || (num_pixels > c_NumPixelsMax))
        return false;
    if ((num_pixels % c_NumSimdElements) != 0)
        return false;
    if (!AlignedMem::IsAligned(pb_src, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pb_mask, c_Alignment))
        return false;
    return true;
}
