//------------------------------------------------
//               Ch08_05_bm.cpp
//------------------------------------------------

#include "Ch08_05.h"
#include "BmThreadTimer.h"

void MatrixMulF32_bm(void)
{
    std::cout << "\nRunning benchmark function MatrixMulF32_bm - please wait\n";

    const size_t a_nrows = 256;
    const size_t a_ncols = 256;
    const size_t b_nrows = a_ncols;
    const size_t b_ncols = 256;
    const size_t c_nrows = a_nrows;
    const size_t c_ncols = b_ncols;

    MatrixF32 a(a_nrows, a_ncols);
    MatrixF32 b(b_nrows, b_ncols);
    MatrixF32 c1(c_nrows, c_ncols);
    MatrixF32 c2(c_nrows, c_ncols);

    InitMat(c1, c2, a, b);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        MatrixMulF32_Cpp(c1, a, b);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        MatrixMulF32_Iavx512(c2, a, b);
        bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch08_05_MatrixMulF32_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
