//------------------------------------------------
//               Ch18_06_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch18_06.h"
#include "MT_Convolve.h"
#include "BmThreadTimer.h"

extern void Convolve1D_F32_bm(void)
{
    std::cout << "\nRunning benchmark function Convolve1D_F32_bm - please wait\n";

    const std::vector<float> kernel { 0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f };
    const size_t num_pts = 1000000;

    std::vector<float> x(num_pts);
    GenSignal1D(x, c_RngSeed);

    std::vector<float> y1(num_pts);
    std::vector<float> y2(num_pts);
    std::vector<float> y3(num_pts);

    const size_t num_it = 500;
    const size_t num_alg = 3;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        Convolve1D_F32_Cpp(y1, x, kernel);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        Convolve1D_F32_Aavx512(y2.data(), x.data(), kernel.data(), x.size(), kernel.size());
        bmtt.Stop(i, 1);

        bmtt.Start(i, 2);
        Convolve1DKs5_F32_Aavx512(y3.data(), x.data(), kernel.data(), x.size());
        bmtt.Stop(i, 2);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch18_06_Convolve1D_F32_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times saved to file " << fn << '\n';
}
