//------------------------------------------------
//               Ch19_01_misc.cpp
//------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include "Ch19_01.h"
#include "MatrixF32.h"
#include "MT.h"
#include "OS.h"

bool CheckArgs(const MatrixF32& m, const std::vector<float>& v1, const std::vector<float>& v2)
{
    size_t nrows = m.GetNumRows();
    return nrows == v1.size() && nrows == v2.size();
}

bool CompareResults(const std::vector<float>& v1, const std::vector<float>& v2)
{
    size_t n1 = v1.size();
    const float eps = 1.0e-4f;

    if (n1 != v2.size())
        return false;

    for (size_t i = 0; i < n1; i++)
    {
        if (fabs(v1[i] - v2[i]) > eps)
            return false;
    }

    return true;
}

void Init(MatrixF32& x)
{
    const float rng_min = 0.1f;
    const float rng_max = 100.0f;
    const unsigned int rng_seed = 3333;

    MT::FillMatrixFP(x.Data(), x.GetNumRows(), x.GetNumCols(), rng_min, rng_max, rng_seed);
    x.SetOstreamW(6);
}

void SaveResults(const char* bn, const MatrixF32& x,
    const std::vector<float>& row_means1, const std::vector<float>& row_means2, const std::vector<float>& row_means3, 
    const std::vector<float>& row_sds1, const std::vector<float>& row_sds2, const std::vector<float>& row_sds3)
{
    const size_t w1 = 4;
    const size_t w2 = 10;
    const char nl = '\n';
    const size_t nrows_max = 100;
    const size_t ncols_max = 50;
    
    std::string fn(bn);
    fn += OS::GetComputerName();
    fn += std::string(".txt");

    std::ofstream ofs(fn);

    if (x.GetNumRows() > nrows_max)
        ofs << "Matrix file save disabled for nrows > " << nrows_max << nl;
    else if (x.GetNumCols() > ncols_max)
        ofs << "Matrix file save disabled for ncols > " << ncols_max << nl;
    else
    {
        ofs << std::fixed << std::setprecision(2);
        ofs << "\nMatrix x\n" << x;
    }

    ofs << std::fixed << std::setprecision(4);

    ofs << "\nRow means\n";
    for (size_t i = 0; i < row_means1.size(); i++)
    {
        ofs << std::setw(w1) << i;
        ofs << std::setw(w2) << row_means1[i];
        ofs << std::setw(w2) << row_means2[i];
        ofs << std::setw(w2) << row_means3[i];
        ofs << nl;
    }

    ofs << "\nRow standard deviations\n";
    for (size_t i = 0; i < row_means1.size(); i++)
    {
        ofs << std::setw(w1) << i;
        ofs << std::setw(w2) << row_sds1[i];
        ofs << std::setw(w2) << row_sds2[i];
        ofs << std::setw(w2) << row_sds3[i];
        ofs << nl;
    }

    ofs.close();
    std::cout << "Results saved to file " << fn << nl;
}
