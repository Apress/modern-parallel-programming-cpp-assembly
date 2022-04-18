//------------------------------------------------
//               Ch19_02_bm.cpp
//------------------------------------------------

#include <iostream>
#include <array>
#include "Ch19_02.h"
#include "BmThreadTimer.h"

void Convolve1Dx2_F32_bm(void)
{
    std::cout << "\nRunning benchmark function Convolve1Dx2_F32_bm - please wait\n";

    const char* fn_src = c_TestImageFileName;
    std::vector<size_t> im_sizes { 1024, 2048, 3072, 4096 };
    const size_t ns = im_sizes.size();
    const size_t num_it = 500;
    BmThreadTimer bmtt(num_it, ns * 2);

    for (size_t alg_id = 0; alg_id < ns; alg_id++)
    {
        std::array<CD_1Dx2, 3> cd;                      // Note: cd[2] is not used below
        InitConvData1Dx2(cd, fn_src, im_sizes[alg_id]);
        const size_t num_it = 500;

        for (size_t i = 0; i < num_it; i++)
        {
            bmtt.Start(i, alg_id * 2);
            Convolve1Dx2_F32a_Iavx512(cd[0]);
            bmtt.Stop(i, alg_id * 2);

            bmtt.Start(i, alg_id * 2 + 1);
            Convolve1Dx2_F32b_Iavx512(cd[1]);
            bmtt.Stop(i, alg_id * 2 + 1);

            if ((i % 25) == 0)
                std::cout << '.' << std::flush;
        }

        std::cout << '\n';
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch19_02_Convolve1Dx2_F32_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times saved to file " << fn << '\n';
}
