//------------------------------------------------
//               Ch05_09_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch05_09.h"
#include "BmThreadTimer.h"

void CalcMatrixInvF64_bm(void)
{
    std::cout << "\nRunning benchmark function CalcMatrixInvF64_bm - please wait\n";

    double epsilon;
    MatrixF64 a = GetTestMatrix(4, &epsilon);
    size_t nrows = a.GetNumRows();
    size_t ncols = a.GetNumCols();
    MatrixF64 a_inv1(nrows, ncols);
    MatrixF64 a_inv2(nrows, ncols);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    const size_t num_ops = 5000;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        for (size_t j = 0; j < num_ops; j++)
            MatrixInvF64_Cpp(a_inv1, a, epsilon);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        for (size_t j = 0; j < num_ops; j++)
            MatrixInvF64_Iavx2(a_inv2, a, epsilon);
        bmtt.Stop(i, 1);

        if ((i % 10) == 0)
            std::cout << '.' << std::flush;
    }

    std::cout << '\n';
    std::string fn = bmtt.BuildCsvFilenameString("Ch05_09_CalcMatrixInvF64_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
