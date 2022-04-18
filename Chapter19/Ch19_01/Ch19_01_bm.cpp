//------------------------------------------------
//               Ch19_01_bm.cpp
//------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include "MatrixF32.h"
#include "Ch19_01.h"
#include "BmThreadTimer.h"

void CalcRowStatsF32_bm(void)
{
    std::cout << "\nRunning benchmark function CalcRowStatsF32_bm - please wait\n";

    std::vector<size_t> mat_sizes { 1024, 1536, 2048, 2560, 3072, 3584, 4096 };
    const size_t ns = mat_sizes.size();
    const size_t num_it = 500;
    BmThreadTimer bmtt(num_it, ns * 2);

    for (size_t alg_id = 0; alg_id < ns; alg_id++)
    {
        size_t x_nrows = mat_sizes[alg_id];
        size_t x_ncols = mat_sizes[alg_id] + 15;

        MatrixF32 x(x_nrows, x_ncols);
        std::vector<float> row_means1(x_nrows);
        std::vector<float> row_means2(x_nrows);
        std::vector<float> row_sds2(x_nrows);
        std::vector<float> row_sds1(x_nrows);

        Init(x);

        for (size_t i = 0; i < num_it; i++)
        {
            bmtt.Start(i, alg_id * 2);
            CalcRowStatsF32a_Iavx512(x, row_means1, row_sds1);
            bmtt.Stop(i, alg_id * 2);

            bmtt.Start(i, alg_id * 2 + 1);
            CalcRowStatsF32b_Iavx512(x, row_means2, row_sds2);
            bmtt.Stop(i, alg_id * 2 + 1);

            if ((i % 50) == 0)
                std::cout << '.' << std::flush;
        }

        std::cout << '\n';
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch19_01_CalcRowStatsF32_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times saved to file " << fn << '\n';
}
