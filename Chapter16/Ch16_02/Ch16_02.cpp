//------------------------------------------------
//               Ch16_02.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch16_02.h"

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
        std::cout << "Ch16_02 exception: " << ex.what() << '\n';
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

    size_t sizes[3];
    sizes[0] = c2.GetNumRows();
    sizes[1] = c2.GetNumCols();
    sizes[2] = a.GetNumCols();

    InitMat(c1, c2, a, b);

    MatrixMulF32_Cpp(c1, a, b);
    MatrixMulF32_Aavx2(c2.Data(), a.Data(), b.Data(), sizes);

    const float epsilon = 1.0e-9f;
    bool is_equal = MatrixF32::IsEqual(c1, c2, epsilon);

    std::cout << "Results for MatrixMulF32\n";

    if (is_equal)
        std::cout << "Matrix compare passed\n";
    else
        std::cout << "Matrix compare failed!\n";

    SaveResults(c1, c2, a, b);
}
