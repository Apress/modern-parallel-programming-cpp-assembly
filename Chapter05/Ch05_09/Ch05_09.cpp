//------------------------------------------------
//               Ch05_09.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Ch05_09.h"
#include "MatrixF64.h"

static void CalcMatrixInvF64(void);

int main()
{
    try
    {
        CalcMatrixInvF64();
        CalcMatrixInvF64_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch05_09 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void CalcMatrixInvF64(void)
{
    const size_t w = 7;
    const char nl = '\n';
    const std::string sep(75, '-');
    const bool display_rounded = true;
    const size_t num_test_mats = GetNumTestMatrices();

    for (size_t id = 0; id < num_test_mats; id++)
    {
        double epsilon;
        MatrixF64 a = GetTestMatrix(id, &epsilon);
        size_t nrows = a.GetNumRows();
        size_t ncols = a.GetNumCols();

        MatrixF64 a_inv1(nrows, ncols);
        MatrixF64 a_inv2(nrows, ncols);

        bool is_singular1 = MatrixInvF64_Cpp(a_inv1, a, epsilon);
        bool is_singular2 = MatrixInvF64_Iavx2(a_inv2, a, epsilon);

        if (is_singular1 != is_singular2)
            throw std::runtime_error("CalcMatrixInvF64() - is_singular discrepancy error");

        if (id > 0)
            std::cout << sep << nl << nl;

        a.SetOstreamW(w);

        std::cout << std::fixed << std::setprecision(3);
        std::cout << "Test Matrix #" << id << nl;
        std::cout << a << nl;

        if (is_singular1)
            std::cout << "Matrix is singular\n";
        else
        {
            if (!MatrixF64::IsEqual(a_inv1, a_inv2, epsilon))
                throw std::runtime_error("CalcMatrixInvF64() - matrix element discrepancy error");

            MatrixF64 a_I1 = a_inv1 * a;

            a_inv1.SetOstreamW(w);
            a_I1.SetOstreamW(w);

            std::cout << "Matrix a_inv1\n" << a_inv1 << nl;

            if (display_rounded)
                a_I1.RoundToI(epsilon);

            std::cout << "Matrix a_I1\n" << a_I1 << nl;
        }
    }
}
