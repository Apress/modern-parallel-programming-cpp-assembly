//------------------------------------------------
//               Ch06_03_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch06_03.h"
#include "BmThreadTimer.h"

void Convolve2D_F32_bm(void)
{
    std::cout << "\nRunning benchmark function Convolve2D_F32_bm - please wait\n";

    const char* fn_src = "../../Data/ImageE.png";

    std::array<CD_2D, 2> cd;
    Init2D(cd, fn_src, c_KernelID_BM);
   
    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        Convolve2D_F32_Cpp(cd[0]);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        Convolve2D_F32_Iavx2(cd[1]);
        bmtt.Stop(i, 1);

        if ((i % 10) == 0)
            std::cout << '.' << std::flush;
    }

    std::cout << '\n';
    std::string fn = bmtt.BuildCsvFilenameString("Ch06_03_Convolve2D_F32_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times saved to file " << fn << '\n';
}
