//------------------------------------------------
//               Ch19_01.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include "Ch19_01.h"
#include "MatrixF32.h"

static void CalcRowStatsF32(void);

int main()
{
    try
    {
        CalcRowStatsF32();
        CalcRowStatsF32_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch19_01 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void CalcRowStatsF32(void)
{
    const size_t x_nrows = 5;
    const size_t x_ncols = 47;
    MatrixF32 x(x_nrows, x_ncols);
    std::vector<float> row_means1(x_nrows);
    std::vector<float> row_means2(x_nrows);
    std::vector<float> row_means3(x_nrows);
    std::vector<float> row_sds1(x_nrows);
    std::vector<float> row_sds2(x_nrows);
    std::vector<float> row_sds3(x_nrows);
    const char* bn_results = "Ch19_01_CalcRowStatsF32_Results_";

    // Calculate row means
    Init(x);
    CalcRowStatsF32_Cpp(x, row_means1, row_sds1);
    CalcRowStatsF32a_Iavx512(x, row_means2, row_sds2);
    CalcRowStatsF32b_Iavx512(x, row_means3, row_sds3);

    // Display results
    std::cout <<"Results for CalcRowStatsF32()\n";
    SaveResults(bn_results, x, row_means1, row_means2, row_means3, row_sds1, row_sds2, row_sds3);

    bool b0 = CompareResults(row_means1, row_means2);
    bool b1 = CompareResults(row_means2, row_means3);
    bool b2 = CompareResults(row_sds1, row_sds2);
    bool b3 = CompareResults(row_sds2, row_sds3);

    if (b0 && b1 && b2 && b3)
        std::cout << "Compare test passed\n";
    else
        std::cout << "Compare test FAILED\n";
}
