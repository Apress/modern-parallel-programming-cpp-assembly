//------------------------------------------------
//               Ch05_03_bm.cpp
//------------------------------------------------

#include "Ch05_03.h"
#include "BmThreadTimer.h"

void MatrixMulF64_bm(void)
{
    std::cout << "\nRunning benchmark function MatrixMulF64_bm - please wait\n";

    const size_t n = 250;
    const size_t a_nrows = n;
    const size_t a_ncols = n;
    const size_t b_nrows = a_ncols;
    const size_t b_ncols = n;
    const size_t c_nrows = a_nrows;
    const size_t c_ncols = b_ncols;

    MatrixF64 a(a_nrows, a_ncols);
    MatrixF64 b(b_nrows, b_ncols);
    MatrixF64 c1(c_nrows, c_ncols);
    MatrixF64 c2(c_nrows, c_ncols);

    InitMat(c1, c2, a, b);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        MatrixMulF64_Cpp(c1, a, b);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        MatrixMulF64_Iavx2(c2, a, b);
        bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch05_03_MatrixMulF64_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
