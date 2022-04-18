//------------------------------------------------
//               Ch06_02_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch06_02.h"
#include "MT_Convolve.h"
#include "BmThreadTimer.h"

extern void Convolve1D_F64_bm(void)
{
    std::cout << "\nRunning benchmark function Convolve1D_F64_bm - please wait\n";

    const std::vector<double> kernel { 0.0625, 0.25, 0.375, 0.25, 0.0625 };
    const size_t num_pts = 1000000;

    std::vector<double> x(num_pts);
    GenSignal1D(x, c_RngSeed);

    std::vector<double> y1(num_pts);
    std::vector<double> y2(num_pts);
    std::vector<double> y3(num_pts);

    const size_t num_it = 500;
    const size_t num_alg = 3;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        Convolve1D_F64_Cpp(y1, x, kernel);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        Convolve1D_F64_Iavx2(y2, x, kernel);
        bmtt.Stop(i, 1);

        bmtt.Start(i, 2);
        Convolve1DKs5_F64_Iavx2(y3, x, kernel);
        bmtt.Stop(i, 2);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch06_02_Convolve1D_F64_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times saved to file " << fn << '\n';
}
