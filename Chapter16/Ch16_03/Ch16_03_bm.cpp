//------------------------------------------------
//               Ch16_03_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch16_03.h"
#include "BmThreadTimer.h"

void MatrixMul4x4F32_bm(void)
{
    std::cout << "\nRunning benchmark function MatrixMul4x4F32_bm - please wait\n";

    const size_t nrows = 4;
    const size_t ncols = 4;
    MatrixF32 a(nrows, ncols);
    MatrixF32 b(nrows, ncols);
    MatrixF32 c1(nrows, ncols);
    MatrixF32 c2(nrows, ncols);
    MatrixF32 c3(nrows, ncols);

    InitMat(c1, c2, c3, a, b);

    const size_t num_it = 500;
    const size_t num_alg = 3;
    const size_t num_ops = 1000000;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        for (size_t j = 0; j < num_ops; j++)
            MatrixMul4x4F32_Cpp(c1, a, b);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        for (size_t j = 0; j < num_ops; j++)
            MatrixMul4x4F32a_Aavx2(c2.Data(), a.Data(), b.Data());
        bmtt.Stop(i, 1);

        bmtt.Start(i, 2);
        for (size_t j = 0; j < num_ops; j++)
            MatrixMul4x4F32b_Aavx2(c3.Data(), a.Data(), b.Data());
        bmtt.Stop(i, 2);

        if ((i % 10) == 0)
            std::cout << '.' << std::flush;
    }

    std::cout << '\n';
    std::string fn = bmtt.BuildCsvFilenameString("Ch16_03_MatrixMul4x4F32_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
