//------------------------------------------------
//               Ch12_08_fcpp.cpp
//------------------------------------------------

#define _USE_MATH_DEFINES
#include <math.h>
#include "Ch12_08.h"

bool CalcConeAreaVol_Cpp(const double* r, const double* h, int n, double* sa_cone, double* vol_cone)
{
    if (n <= 0)
        return false;

    for (int i = 0; i < n; i++)
    {
        sa_cone[i] = M_PI * r[i] * (r[i] + sqrt(r[i] * r[i] + h[i] * h[i]));
        vol_cone[i] = M_PI * r[i] * r[i] * h[i] / 3.0;
    }

    return true;
}

