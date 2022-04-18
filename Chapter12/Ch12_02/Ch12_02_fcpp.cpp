//------------------------------------------------
//               Ch12_02_fcpp.cpp
//------------------------------------------------

#include "Ch12_02.h"
#include <cmath>

double CalcDistance_Cpp(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double temp_x = (x2 - x1) * (x2 - x1);
    double temp_y = (y2 - y1) * (y2 - y1);
    double temp_z = (z2 - z1) * (z2 - z1);
    double dist = sqrt(temp_x + temp_y + temp_z);
    return dist;
}
