//------------------------------------------------
//               Ch06_02_misc.cpp
//------------------------------------------------

#include "Ch06_02.h"

bool CheckArgs(std::vector<double>& y, const std::vector<double>& x, const std::vector<double>& kernel)
{
    if ((kernel.size() & 1) == 0)
        return false;
    if (y.size() != x.size())
        return false;
    if (y.size() < kernel.size())
        return false;
    return true;
}

