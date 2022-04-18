//------------------------------------------------
//               Ch16_05_misc.cpp
//------------------------------------------------

#include "Ch16_05.h"

bool CheckArgs(std::vector<float>& y, const std::vector<float>& x, const std::vector<float>& kernel)
{
    if ((kernel.size() & 1) == 0)
        return false;

    if (y.size() != x.size())
        return false;

    if (y.size() < kernel.size())
        return false;

    return true;
}
