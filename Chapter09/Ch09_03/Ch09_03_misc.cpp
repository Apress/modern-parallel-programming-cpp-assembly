//------------------------------------------------
//               Ch09_03_misc.cpp
//------------------------------------------------

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include "Ch09_03.h"
#include "MT.h"

bool CheckArgs(const std::vector<double>& bsa, const std::vector<double>& ht,
    const std::vector<double>& wt)
{
    if (ht.size() != wt.size())
        return false;

    if (bsa.size() != ht.size() * 3)
        return false;

    return true;
}

bool CompareResults(const std::vector<double>& bsa1,
    const std::vector<double>& bsa2)
{
    double epsilon = 1.0e-9;

    if (bsa1.size() != bsa2.size())
        return false;

    size_t n = bsa1.size();

    for (size_t i = 0; i < n; i++)
    {
        if (fabs(bsa1[i] - bsa2[i]) > epsilon)
            return false;
    }

    return true;
}

void FillHeightWeightVectors(std::vector<double>& ht, std::vector<double>& wt)
{
    const int rng_min_ht = 140;             // cm
    const int rng_max_ht =  204;            // cm
    const int rng_min_wt = 40;              // kg
    const int rng_max_wt = 140;             // kg
    const unsigned int rng_seed_ht = 803;
    const unsigned int rng_seed_wt = 807;

    MT::FillArray(ht.data(), ht.size(), rng_min_ht, rng_max_ht, rng_seed_ht);
    MT::FillArray(wt.data(), wt.size(), rng_min_wt, rng_max_wt, rng_seed_wt);
}
