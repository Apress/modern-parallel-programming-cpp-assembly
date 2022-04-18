//------------------------------------------------
//               Ch12_02.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch12_02.h"

static void CalcDistance(void);

int main()
{
    CalcDistance();
    return 0;
}

static void CalcDistance(void)
{
    const size_t n = 20;
    double x1[n], y1[n], z1[n], dist1[n];
    double x2[n], y2[n], z2[n], dist2[n];

    InitArrays(x1, y1, z1, n, 29);
    InitArrays(x2, y2, z2, n, 37);

    for (size_t i = 0; i < n; i++)
    {
        dist1[i] = CalcDistance_Cpp(x1[i], y1[i], z1[i], x2[i], y2[i], z2[i]);
        dist2[i] = CalcDistance_Aavx(x1[i], y1[i], z1[i], x2[i], y2[i], z2[i]);
    }

    size_t w1 = 3, w2 = 8;
    std::cout << std::fixed;

    for (size_t i = 0; i < n; i++)
    {
        std::cout << "i: " << std::setw(w1) << i << "  ";

        std::cout << std::setprecision(0);

        std::cout << "p1(";
        std::cout << std::setw(w1) << x1[i] << ",";
        std::cout << std::setw(w1) << y1[i] << ",";
        std::cout << std::setw(w1) << z1[i] << ") | ";

        std::cout << "p2(";
        std::cout << std::setw(w1) << x2[i] << ",";
        std::cout << std::setw(w1) << y2[i] << ",";
        std::cout << std::setw(w1) << z2[i] << ") | ";

        std::cout << std::setprecision(4);
        std::cout << "dist1: " << std::setw(w2) << dist1[i] << " | ";
        std::cout << "dist2: " << std::setw(w2) << dist2[i] << '\n';
    }
}
