//------------------------------------------------
//               Ch05_05_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch05_05.h"
#include "BmThreadTimer.h"

void MatrixMul4x4F64_bm(void)
{
    std::cout << "\nRunning benchmark function MatrixMul4x4F64_bm - please wait\n";

    const size_t nrows = 4;
    const size_t ncols = 4;
    MatrixF64 a(nrows, ncols);
    MatrixF64 b(nrows, ncols);
    MatrixF64 c1(nrows, ncols);
    MatrixF64 c2(nrows, ncols);

    InitMat(c1, c2, a, b);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    const size_t num_ops = 1000000;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        for (size_t j = 0; j < num_ops; j++)
            MatrixMul4x4F64_Cpp(c1, a, b);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        for (size_t j = 0; j < num_ops; j++)
            MatrixMul4x4F64_Iavx2(c2, a, b);
        bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch05_05_MatrixMul4x4F64_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
