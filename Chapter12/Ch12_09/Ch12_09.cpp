//------------------------------------------------
//               Ch12_09.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch12_09.h"

static void CalcBSA(void);

int main()
{
    CalcBSA();
    return 0;
}

static void CalcBSA(void)
{
    const int n = 6;
    const double ht[n] = { 150, 160, 170, 180, 190, 200 };
    const double wt[n] = { 50.0, 60.0, 70.0, 80.0, 90.0, 100.0 };
    double bsa1_a[n], bsa1_b[n];
    double bsa2_a[n], bsa2_b[n];
    double bsa3_a[n], bsa3_b[n];

    CalcBSA_Cpp(ht, wt, n, bsa1_a, bsa2_a, bsa3_a);
    CalcBSA_Aavx(ht, wt, n, bsa1_b, bsa2_b, bsa3_b);

    const char sp = ' ';
    const size_t w1 = 6;
    const size_t w2 = 9;

    std::cout << std::fixed;
    std::cout << "----- Results for CalcBSA -----\n";

    for (int i = 0; i < n; i++)
    {
        std::cout << std::setprecision(1);
        std::cout << "height: " << std::setw(w1) << ht[i] << " (cm)\n";
        std::cout << "weight: " << std::setw(w1) << wt[i] << " (kg)\n";
        std::cout << std::setprecision(6);

        std::cout << "BSA (C++): ";
        std::cout << std::setw(w2) << bsa1_a[i]  << sp;
        std::cout << std::setw(w2) << bsa2_a[i]  << sp;
        std::cout << std::setw(w2) << bsa3_a[i]  << " (sq. m)\n";

        std::cout << "BSA (AVX): ";
        std::cout << std::setw(w2) << bsa1_b[i]  << sp;
        std::cout << std::setw(w2) << bsa2_b[i]  << sp;
        std::cout << std::setw(w2) << bsa3_b[i]  << " (sq. m)\n\n";
    }
}
