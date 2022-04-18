//------------------------------------------------
//               Ch05_05.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch05_05.h"

static void MatrixMul4x4F64(void);

int main()
{
    try
    {
        MatrixMul4x4F64();
        MatrixMul4x4F64_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch05_05 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void MatrixMul4x4F64(void)
{
    const char nl = '\n';
    const size_t nrows = 4;
    const size_t ncols = 4;
    MatrixF64 a(nrows, ncols);
    MatrixF64 b(nrows, ncols);
    MatrixF64 c1(nrows, ncols);
    MatrixF64 c2(nrows, ncols);

    InitMat(c1, c2, a, b);

    MatrixMul4x4F64_Cpp(c1, a, b);
    MatrixMul4x4F64_Iavx2(c2, a, b);

    std::cout << std::fixed << std::setprecision(1);

    std::cout << "\nResults for MatrixMul4x4F64\n";
    std::cout << "Matrix a\n" << a << nl;
    std::cout << "Matrix b\n" << b << nl;
    std::cout << "Matrix c1\n" << c1 << nl;
    std::cout << "Matrix c2\n" << c2 << nl;

    const double epsilon = 1.0e-9;
    bool ie12 = MatrixF64::IsEqual(c1, c2, epsilon);

    if (ie12)
        std::cout << "\nMatrix compare passed\n";
    else
        std::cout << "\nMatrix compare failed!\n";
}
