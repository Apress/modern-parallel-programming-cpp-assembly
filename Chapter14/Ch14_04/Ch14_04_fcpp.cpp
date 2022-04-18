//------------------------------------------------
//               Ch14_04_fcpp.cpp
//------------------------------------------------

#include <cmath>
#include "Ch14_04.h"

bool CalcDistancesF64(PA& pa)
{
    if (!CheckArgs(pa))
        return false;

    size_t num_points = pa.NumPoints;

    for (size_t i = 0; i < num_points; i++)
    {
        double temp1 = pa.X1[i] - pa.X2[i];
        double temp2 = pa.Y1[i] - pa.Y2[i];

        pa.Dist1[i] = sqrt(temp1 * temp1 + temp2 * temp2);
    }

    return true;
}

void CompareDistancesF64(PA& pa, double cmp_val)
{
    size_t num_points = pa.NumPoints;

    for (size_t i = 0; i < num_points; i++)
    {
        double temp1 = pa.Dist1[i];
        double temp2 = (temp1 >= cmp_val) ? temp1 * -2.0 : temp1;

        pa.DistCmp1[i] = temp2;
    }
}
