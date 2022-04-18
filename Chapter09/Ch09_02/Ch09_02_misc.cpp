//------------------------------------------------
//               Ch09_02_misc.cpp
//------------------------------------------------

#include <vector>
#include <stdexcept>
#include <cmath>
#include "Ch09_02.h"
#include "MT.h"

bool CheckArgs(const std::vector<float>& v1, const std::vector<float>& v2,
    const std::vector<float>& v3, const std::vector<float>& v4)
{
    size_t n = v1.size();
    return (n == v2.size() && n == v3.size() && n == v4.size());
}

bool CompareResults(const std::vector<float>& v1, const std::vector<float>& v2)
{
    float epsilon = 1.0e-4f;

    if (v1.size() != v2.size())
        return false;

    size_t n = v1.size();

    for (size_t i = 0; i < n; i++)
    {
        if (fabs(v1[i] - v2[i]) > epsilon)
            return false;
    }

    return true;
}

void FillVectorsRect(std::vector<float>& x, std::vector<float>& y)
{
    if (x.size() != y.size())
        throw std::runtime_error("FillVectorsRect() - non-conforming vectors");

    const int rng_min = -25;
    const int rng_max =  25;
    const unsigned int rng_seed_x = 699;
    const unsigned int rng_seed_y = 701;

    MT::FillArray(x.data(), x.size(), rng_min, rng_max, rng_seed_x, true);
    MT::FillArray(y.data(), y.size(), rng_min, rng_max, rng_seed_y, true);
}

void FillVectorsPolar(std::vector<float>& r, std::vector<float>& a)
{
    if (r.size() != a.size())
        throw std::runtime_error("FillVectorsPolar() - non-conforming vectors");

    const int rng_min_r = 1;
    const int rng_max_r =  50;
    const int rng_min_a = -359;
    const int rng_max_a =  359;
    const unsigned int rng_seed_r = 703;
    const unsigned int rng_seed_a = 707;

    MT::FillArray(r.data(), r.size(), rng_min_r, rng_max_r, rng_seed_r, true);
    MT::FillArray(a.data(), a.size(), rng_min_a, rng_max_a, rng_seed_a, true);
}
