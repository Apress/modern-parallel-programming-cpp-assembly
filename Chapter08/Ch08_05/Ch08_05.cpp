//------------------------------------------------
//               Ch08_05.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch08_05.h"

static void MatrixMulF32(void);

int main()
{
    try
    {
        MatrixMulF32();
        MatrixMulF32_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch08_05 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void MatrixMulF32()
{
    const size_t a_nrows = 11;
    const size_t a_ncols = 13;
    const size_t b_nrows = a_ncols;
    const size_t b_ncols = 19;
    const size_t c_nrows = a_nrows;
    const size_t c_ncols = b_ncols;

    MatrixF32 a(a_nrows, a_ncols);
    MatrixF32 b(b_nrows, b_ncols);
    MatrixF32 c1(c_nrows, c_ncols);
    MatrixF32 c2(c_nrows, c_ncols);

    InitMat(c1, c2, a, b);
    MatrixMulF32_Cpp(c1, a, b);
    MatrixMulF32_Iavx512(c2, a, b);

    std::cout << "Results for MatrixMulF32\n";

    if (c1 == c2)
        std::cout << "Matrix compare passed\n";
    else
        std::cout << "Matrix compare failed!\n";

    SaveResults(c1, c2, a, b);
}
