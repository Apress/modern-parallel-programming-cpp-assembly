//------------------------------------------------
//               Ch09_03_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch09_03.h"
#include "BmThreadTimer.h"

void CalcBSA_bm(void)
{
    std::cout << "\nRunning benchmark function CalcBSA_bm - please wait\n";

    const size_t n = 200000;
    std::vector<double> heights(n);
    std::vector<double> weights(n);
    std::vector<double> bsa1(n * 3);
    std::vector<double> bsa2(n * 3);

    FillHeightWeightVectors(heights, weights);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        CalcBSA_F64_Cpp(bsa1, heights, weights);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        CalcBSA_F64_Iavx(bsa2, heights, weights);
        bmtt.Stop(i, 1);
    }

    std::cout << '\n';
    std::string fn = bmtt.BuildCsvFilenameString("Ch09_03_CalcBSA_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
