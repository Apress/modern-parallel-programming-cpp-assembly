//------------------------------------------------
//               Ch12_08.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch12_08.h"

static void CalcConeAreaVol(void);

int main()
{
    CalcConeAreaVol();
    return 0;
}

static void CalcConeAreaVol(void)
{
    const int n = 7;
    const double r[n] = { 1, 1, 2, 2, 3, 3, 4.25 };
    const double h[n] = { 1, 2, 3, 4, 5, 10, 12.5 };
    double sa_cone1[n], sa_cone2[n], vol_cone1[n], vol_cone2[n];

    CalcConeAreaVol_Cpp(r, h, n, sa_cone1, vol_cone1);
    CalcConeAreaVol_A(r, h, n, sa_cone2, vol_cone2);

    std::cout << "----- Results for CalcConeAreaVol -----\n";
    std::cout << std::fixed;

    const size_t w = 14;
    const char nl = '\n';
    const char sp = ' ';

    for (int i = 0; i < n; i++)
    {
        std::cout << std::setprecision(2);
        std::cout << "r/h: " << std::setw(w) << r[i] << sp;
        std::cout << std::setw(w) << h[i] << nl;

        std::cout << std::setprecision(6);
        std::cout << "sa:  " << std::setw(w) << sa_cone1[i] << sp;
        std::cout << std::setw(w) << sa_cone2[i] << nl;

        std::cout << "vol: " << std::setw(w) << vol_cone1[i] << sp;
        std::cout << std::setw(w) << vol_cone2[i] << nl;
        std::cout << nl;
    }
}

