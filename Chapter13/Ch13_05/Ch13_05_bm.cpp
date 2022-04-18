//------------------------------------------------
//               Ch13_05_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch13_05.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"

void CalcMinMaxU8_bm(void)
{
    std::cout << "\nRunning benchmark function CalcMinMaxU8_bm - please wait\n";

    size_t n = c_NumElements;
    AlignedArray<uint8_t> x_aa(n, 16);
    uint8_t* x = x_aa.Data();

    InitArray(x, n, c_RngSeedVal);

    uint8_t x_min0 = 0, x_max0 = 0;
    uint8_t x_min1 = 0, x_max1 = 0;

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        CalcMinMaxU8_Cpp(&x_min0, &x_max0, x, n);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        CalcMinMaxU8_Aavx(&x_min1, &x_max1, x, n);
        bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch13_05_CalcMinMaxU8_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
