//------------------------------------------------
//               Ch02_07_bm.cpp
//------------------------------------------------

#include "Ch02_07.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"

void CalcMeanU8_bm(void)
{
    std::cout << "\nRunning benchmark function CalcMeanU8_bm - please wait\n";

    size_t n = c_NumElements;
    AlignedArray<uint8_t> x_aa(n, c_Alignment);
    uint8_t* x = x_aa.Data();

    InitArray(x, n, c_RngSeedVal);

    uint64_t sum_x0, sum_x1;
    double mean_x0, mean_x1;

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        CalcMeanU8_Cpp(&mean_x0, &sum_x0, x, n);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        CalcMeanU8_Iavx(&mean_x1, &sum_x1, x, n);
        bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch02_07_CalcMeanU8_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
