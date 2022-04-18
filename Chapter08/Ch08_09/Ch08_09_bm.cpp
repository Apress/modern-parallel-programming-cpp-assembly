//------------------------------------------------
//               Ch08_09_bm.cpp
//------------------------------------------------

#include <iostream>
#include <array>
#include "Ch08_09.h"
#include "BmThreadTimer.h"

void Convolve1Dx2_F32_bm(void)
{
    std::cout << "\nRunning benchmark function Convolve1Dx2_F32_bm - please wait\n";

    const char* fn_src = "../../Data/ImageE.png";

    std::array<CD_1Dx2, 2> cd;
    InitConvData1Dx2(cd, fn_src);
   
    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        Convolve1Dx2_F32_Cpp(cd[0]);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        Convolve1Dx2_F32_Iavx512(cd[1]);
        bmtt.Stop(i, 1);

        if ((i % 10) == 0)
            std::cout << '.' << std::flush;
    }

    std::cout << '\n';
    std::string fn = bmtt.BuildCsvFilenameString("Ch08_09_Convolve1Dx2_F32_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times saved to file " << fn << '\n';
}
