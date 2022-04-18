//------------------------------------------------
//               Ch08_05_misc.cpp
//------------------------------------------------

#include <fstream>
#include "Ch08_05.h"
#include "MT.h"

bool CheckArgs(const MatrixF32& c, const MatrixF32& a, const MatrixF32& b)
{
    size_t a_nrows = a.GetNumRows();
    size_t a_ncols = a.GetNumCols();
    size_t b_nrows = b.GetNumRows();
    size_t b_ncols = b.GetNumCols();
    size_t c_nrows = c.GetNumRows();
    size_t c_ncols = c.GetNumCols();

    if (a_ncols != b_nrows)
        return false;

    if (c_nrows != a_nrows)
        return false;

    if (c_ncols != b_ncols)
        return false;

    return true;
}

void InitMat(MatrixF32& c1, MatrixF32& c2, MatrixF32& a, MatrixF32& b)
{
    int rng_min = 2;
    int rng_max = 50;
    unsigned int rng_seed_a = 42;
    unsigned int rng_seed_b = 43;

    MT::FillMatrix(a.Data(), a.GetNumRows(), a.GetNumCols(), rng_min, rng_max, rng_seed_a, true);
    MT::FillMatrix(b.Data(), b.GetNumRows(), b.GetNumCols(), rng_min, rng_max, rng_seed_b, true);

    const int w = 8;
    c1.SetOstreamW(w);
    c2.SetOstreamW(w);
    a.SetOstreamW(w);
    b.SetOstreamW(w);
}

void SaveResults(const MatrixF32& c1, const MatrixF32& c2, const MatrixF32& a, const MatrixF32& b)
{
    const char nl = '\n';
    
    std::string fn("Ch08_05_MatrixMulF32_");
    fn += OS::GetComputerName();
    fn += std::string(".txt");

    std::ofstream ofs(fn);
    ofs << "\nMatrix a\n" << a << nl;
    ofs << "\nMatrix b\n" << b << nl;
    ofs << "\nMatrix c1\n" << c1 << nl;
    ofs << "\nMatrix c2\n" << c2 << nl;

    ofs.close();

    std::cout << "Results saved to file " << fn << nl;
}
