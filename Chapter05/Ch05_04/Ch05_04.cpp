//------------------------------------------------
//               Ch05_04.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch05_04.h"

static void MatrixMul4x4F32(void);

int main()
{
    try
    {
        MatrixMul4x4F32();
        MatrixMul4x4F32_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch05_04 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void MatrixMul4x4F32(void)
{
    const char nl = '\n';
    const size_t nrows = 4;
    const size_t ncols = 4;
    MatrixF32 a(nrows, ncols);
    MatrixF32 b(nrows, ncols);
    MatrixF32 c1(nrows, ncols);
    MatrixF32 c2(nrows, ncols);

    InitMat(c1, c2, a, b);

    MatrixMul4x4F32_Cpp(c1, a, b);
    MatrixMul4x4F32_Iavx2(c2, a, b);

    std::cout << std::fixed << std::setprecision(1);

    std::cout << "\nResults for MatrixMul4x4F32\n";
    std::cout << "Matrix a\n" << a << nl;
    std::cout << "Matrix b\n" << b << nl;
    std::cout << "Matrix c1\n" << c1 << nl;
    std::cout << "Matrix c2\n" << c2 << nl;

    const float epsilon = 1.0e-9f;
    bool ie12 = MatrixF32::IsEqual(c1, c2, epsilon);

    if (ie12)
        std::cout << "Matrix compare passed\n";
    else
        std::cout << "Matrix compare failed!\n";
}
