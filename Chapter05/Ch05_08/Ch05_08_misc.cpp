//------------------------------------------------
//               Ch05_08_misc.cpp
//------------------------------------------------

#include <stdexcept>
#include "Ch05_08.h"
#include "MatrixF32.h"
#include "MT.h"

size_t GetNumTestMatrices(void)
{
    return 5;
}

MatrixF32 GetTestMatrix(size_t id, float* epsilon)
{
    *epsilon = c_DefaultEpsilon;

    if (id == 0)
    {
        // Test matrix #0 - non-singular
        MatrixF32 a(4, 4);
        const float a_row0[] = { 2, 7, 3, 4 };
        const float a_row1[] = { 5, 9, 6, 4.75 };
        const float a_row2[] = { 6.5, 3, 4, 10 };
        const float a_row3[] = { 7, 5.25, 8.125, 6 };
        a.SetRow(0, a_row0);
        a.SetRow(1, a_row1);
        a.SetRow(2, a_row2);
        a.SetRow(3, a_row3);
        return a;
    }

    if (id == 1)
    {
        // Test matrix #1 - singular
        MatrixF32 a(4, 4);
        const float a_row0[] = { 2, 0, 0, 1 };
        const float a_row1[] = { 0, 4, 5, 0 };
        const float a_row2[] = { 0, 0, 0, 7 };
        const float a_row3[] = { 0, 0, 0, 6 };
        a.SetRow(0, a_row0);
        a.SetRow(1, a_row1);
        a.SetRow(2, a_row2);
        a.SetRow(3, a_row3);
        return a;
    }

    if (id == 2)
    {
        // Test matrix #2 - non-singular
        MatrixF32 a(5, 5);

        MT::FillMatrix(a.Data(), a.GetNumRows(), a.GetNumCols(), -25, 25, 147, true);
        return a;
    }

    if (id == 3)
    {
        // Test matrix #3 - singular
        MatrixF32 a(6, 6);
        const float a_row0[] = { 2, 0, 0, 1, 0, 3 };
        const float a_row1[] = { 0, 4, 5, 0, 9, -2 };
        const float a_row2[] = { 0, 0, 0, 7, 6, -7 };
        const float a_row3[] = { 0, 0, 0, 6, -9, 0 };
        const float a_row4[] = { -6, 0, 0, 0, 0, 0 };
        const float a_row5[] = { -3, 0, 0, 0, 0, 0 };
        a.SetRow(0, a_row0);
        a.SetRow(1, a_row1);
        a.SetRow(2, a_row2);
        a.SetRow(3, a_row3);
        a.SetRow(4, a_row4);
        a.SetRow(5, a_row5);

        return a;
    }

    if (id == 4)
    {
        // Test matrix #4 - non-singular
        MatrixF32 a(10, 10);

        MT::FillMatrix(a.Data(), a.GetNumRows(), a.GetNumCols(), -25, 25, 149, true);

        *epsilon = 1.0e-4f;
        return a;
    }

    throw std::runtime_error("GetTestMatrix() - invalid id");
};
