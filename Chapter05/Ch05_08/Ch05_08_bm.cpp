//------------------------------------------------
//               Ch05_08_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch05_08.h"
#include "BmThreadTimer.h"

void CalcMatrixInvF32_bm(void)
{
    std::cout << "\nRunning benchmark function CalcMatrixInvF32_bm - please wait\n";

    float epsilon;
    MatrixF32 a = GetTestMatrix(4, &epsilon);
    size_t nrows = a.GetNumRows();
    size_t ncols = a.GetNumCols();
    MatrixF32 a_inv1(nrows, ncols);
    MatrixF32 a_inv2(nrows, ncols);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    const size_t num_ops = 5000;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        for (size_t j = 0; j < num_ops; j++)
            MatrixInvF32_Cpp(a_inv1, a, epsilon);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        for (size_t j = 0; j < num_ops; j++)
            MatrixInvF32_Iavx2(a_inv2, a, epsilon);
        bmtt.Stop(i, 1);

        if ((i % 10) == 0)
            std::cout << '.' << std::flush;
    }

    std::cout << '\n';
    std::string fn = bmtt.BuildCsvFilenameString("Ch05_08_CalcMatrixInvF32_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
