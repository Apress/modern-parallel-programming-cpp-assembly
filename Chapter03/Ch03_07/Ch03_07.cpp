//------------------------------------------------
//               Ch03_07.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include "Ch03_07.h"
#include "AlignedMem.h"

static void CalcDistanceF64(void);

int main()
{
    CalcDistanceF64();
    return 0;
}

static void CalcDistanceF64(void)
{
    AlignedArray<double> x1(c_NumPoints, c_Alignment);
    AlignedArray<double> y1(c_NumPoints, c_Alignment);
    AlignedArray<double> x2(c_NumPoints, c_Alignment);
    AlignedArray<double> y2(c_NumPoints, c_Alignment);
    AlignedArray<double> dist1(c_NumPoints, c_Alignment);
    AlignedArray<double> dist2(c_NumPoints, c_Alignment);
    AlignedArray<double> dist_cmp1(c_NumPoints, c_Alignment);
    AlignedArray<double> dist_cmp2(c_NumPoints, c_Alignment);

    PointArrays pa;

    pa.X1 = x1.Data();
    pa.Y1 = y1.Data();
    pa.X2 = x2.Data();
    pa.Y2 = y2.Data();
    pa.Dist1 = dist1.Data();
    pa.Dist2 = dist2.Data();
    pa.DistCmp1 = dist_cmp1.Data();
    pa.DistCmp2 = dist_cmp2.Data();
    pa.NumPoints = c_NumPoints;

    FillPointArraysF64(pa, c_ArrayFillMin, c_ArrayFillMax, c_RngSeed);

    CalcDistancesF64_Cpp(pa);
    CompareDistancesF64_Cpp(pa, c_CmpVal);

    CalcDistancesF64_Iavx(pa);
    CompareDistancesF64_Iavx(pa, c_CmpVal);

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

    for (size_t i = 0; i < c_NumPoints; i++)
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
