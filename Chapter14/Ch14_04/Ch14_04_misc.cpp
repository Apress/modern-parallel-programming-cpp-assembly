//------------------------------------------------
//               Ch14_04_misc.cpp
//------------------------------------------------

#include <random>
#include "Ch14_04.h"
#include "AlignedMem.h"

bool CheckArgs(PA& pa)
{
    const size_t alignment = c_Alignment;

    if (!AlignedMem::IsAligned(pa.X1, alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.X2, alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.Y1, alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.Y2, alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.Dist1, alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.Dist2, alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.DistCmp1, alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.DistCmp2, alignment))
        return false;

    return true;
}

void FillPAF64(PA& pa, double min_val, double max_val, unsigned int rng_seed)
{
    std::mt19937 rng {rng_seed};
    std::uniform_real_distribution<float> dist {(float)min_val, (float)max_val};

    size_t num_points = pa.NumPoints;

    for (size_t i = 0; i < num_points; i++)
    {
        pa.X1[i] = dist(rng);
        pa.X2[i] = dist(rng);
        pa.Y1[i] = dist(rng);
        pa.Y2[i] = dist(rng);
    }
}
