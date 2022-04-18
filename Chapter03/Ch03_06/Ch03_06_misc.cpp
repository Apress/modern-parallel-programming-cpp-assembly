//------------------------------------------------
//               Ch03_06_misc.cpp
//------------------------------------------------

#include <random>
#include "Ch03_06.h"
#include "AlignedMem.h"

bool CheckArgs(PointArrays& pa)
{
    if (!AlignedMem::IsAligned(pa.X1, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.X2, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.Y1, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.Y2, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.Dist1, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.Dist2, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.DistCmp1, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pa.DistCmp2, c_Alignment))
        return false;

    return true;
}

void FillPointArraysF32(PointArrays& pa, float min_val, float max_val, unsigned int rng_seed)
{
    std::mt19937 rng {rng_seed};
    std::uniform_real_distribution<float> dist {min_val, max_val};

    size_t num_points = pa.NumPoints;

    for (size_t i = 0; i < num_points; i++)
    {
        pa.X1[i] = dist(rng);
        pa.X2[i] = dist(rng);
        pa.Y1[i] = dist(rng);
        pa.Y2[i] = dist(rng);
    }
}
