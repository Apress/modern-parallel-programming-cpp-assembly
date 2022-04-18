//------------------------------------------------
//               Ch14_04.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include "Ch14_04.h"
#include "AlignedMem.h"

int main()
{
    const size_t alignment = c_Alignment;
    const size_t num_points = c_NumPoints;

    AlignedArray<double> x1(num_points, alignment);
    AlignedArray<double> y1(num_points, alignment);
    AlignedArray<double> x2(num_points, alignment);
    AlignedArray<double> y2(num_points, alignment);
    AlignedArray<double> dist1(num_points, alignment);
    AlignedArray<double> dist2(num_points, alignment);
    AlignedArray<double> dist_cmp1(num_points, alignment);
    AlignedArray<double> dist_cmp2(num_points, alignment);

    PA pa;

    pa.X1 = x1.Data();
    pa.Y1 = y1.Data();
    pa.X2 = x2.Data();
    pa.Y2 = y2.Data();
    pa.Dist1 = dist1.Data();
    pa.Dist2 = dist2.Data();
    pa.DistCmp1 = dist_cmp1.Data();
    pa.DistCmp2 = dist_cmp2.Data();
    pa.NumPoints = num_points;

    FillPAF64(pa, c_ArrayFillMin, c_ArrayFillMax, c_RngSeed);

    CalcDistancesF64(pa);
    CalcDistancesF64_Aavx(pa);
    CompareDistancesF64(pa, c_CmpVal);
    CompareDistancesF64_Aavx(pa, &c_CmpVal);

    const size_t w = 9;
    const char nl = '\n';
    std::cout << std::fixed << std::setprecision(3);

    std::cout << std::setw(w) << "X1" << " ";
    std::cout << std::setw(w) << "Y1" << " ";
    std::cout << std::setw(w) << "X2" << " ";
    std::cout << std::setw(w) << "Y2" << " |";
    std::cout << std::setw(w) << "Dist1" << " ";
    std::cout << std::setw(w) << "Dist2" << " |";
    std::cout << std::setw(w) << "DistCmp1" << " ";
    std::cout << std::setw(w) << "DistCmp2" << nl;
    std::cout << std::string(82, '-') << nl;

    for (size_t i = 0; i < num_points; i++)
    {
        std::cout << std::setw(w) << pa.X1[i] << " ";
        std::cout << std::setw(w) << pa.Y1[i] << " ";
        std::cout << std::setw(w) << pa.X2[i] << " ";
        std::cout << std::setw(w) << pa.Y2[i] << " |";
        std::cout << std::setw(w) << pa.Dist1[i] << " ";
        std::cout << std::setw(w) << pa.Dist2[i] << " |";
        std::cout << std::setw(w) << pa.DistCmp1[i] << " ";
        std::cout << std::setw(w) << pa.DistCmp2[i] << nl;
    }
}
