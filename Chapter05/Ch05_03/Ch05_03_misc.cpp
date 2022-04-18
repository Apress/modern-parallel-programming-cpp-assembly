//------------------------------------------------
//               Ch05_03_misc.cpp
//------------------------------------------------

#include <string>
#include <fstream>
#include "Ch05_03.h"
#include "MT.h"

bool CheckArgs(const MatrixF64& c, const MatrixF64& a, const MatrixF64& b)
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

void InitMat(MatrixF64& c1, MatrixF64& c2, MatrixF64& a, MatrixF64& b)
{
    int rng_min = 2;
    int rng_max = 50;
    unsigned int rng_seed_a = 42;
    unsigned int rng_seed_b = 43;

    MT::FillMatrix(a.Data(), a.GetNumRows(), a.GetNumCols(), rng_min, rng_max,
        rng_seed_a, true);
    MT::FillMatrix(b.Data(), b.GetNumRows(), b.GetNumCols(), rng_min, rng_max,
        rng_seed_b, true);

    const int w = 8;
    c1.SetOstreamW(w);
    c2.SetOstreamW(w);
    a.SetOstreamW(w);
    b.SetOstreamW(w);
}

void SaveResults(const MatrixF64& c1, const MatrixF64& c2, const MatrixF64& a,
    const MatrixF64& b)
{
    const char nl = '\n';
    
    std::string fn("Ch05_03_MatrixMulF64_");
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
