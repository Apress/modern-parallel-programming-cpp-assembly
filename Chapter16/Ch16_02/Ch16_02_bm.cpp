//------------------------------------------------
//               Ch16_02_bm.cpp
//------------------------------------------------

#include "Ch16_02.h"
#include "BmThreadTimer.h"

void MatrixMulF32_bm(void)
{
    std::cout << "\nRunning benchmark function MatrixMulF32_bm - please wait\n";

    const size_t n = 250;
    const size_t a_nrows = n;
    const size_t a_ncols = n;
    const size_t b_nrows = a_ncols;
    const size_t b_ncols = n;
    const size_t c_nrows = a_nrows;
    const size_t c_ncols = b_ncols;

    MatrixF32 a(a_nrows, a_ncols);
    MatrixF32 b(b_nrows, b_ncols);
    MatrixF32 c1(c_nrows, c_ncols);
    MatrixF32 c2(c_nrows, c_ncols);

    InitMat(c1, c2, a, b);

    size_t sizes[3];
    sizes[0] = c2.GetNumRows();
    sizes[1] = c2.GetNumCols();
    sizes[2] = a.GetNumCols();

    float* c2_p = c2.Data();
    float* a_p = a.Data();
    float* b_p = b.Data();

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
         bmtt.Start(i, 0);
         MatrixMulF32_Cpp(c1, a, b);
         bmtt.Stop(i, 0);

         bmtt.Start(i, 1);
         MatrixMulF32_Aavx2(c2_p, a_p, b_p, sizes);
         bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch16_02_MatrixMulF32_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
