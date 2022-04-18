//------------------------------------------------
//               Ch16_03_misc.cpp
//------------------------------------------------

#include "Ch16_03.h"

void InitMat(MatrixF32& c1, MatrixF32& c2, MatrixF32& c3, MatrixF32& a, MatrixF32& b)
{
    const float a_row0[] = { 10, 11, 12, 13 };
    const float a_row1[] = { 20, 21, 22, 23 };
    const float a_row2[] = { 30, 31, 32, 33 };
    const float a_row3[] = { 40, 41, 42, 43 };

    const float b_row0[] = { 100, 101, 102, 103 };
    const float b_row1[] = { 200, 201, 202, 203 };
    const float b_row2[] = { 300, 301, 302, 303 };
    const float b_row3[] = { 400, 401, 402, 403 };

    a.SetRow(0, a_row0);
    a.SetRow(1, a_row1);
    a.SetRow(2, a_row2);
    a.SetRow(3, a_row3);

    b.SetRow(0, b_row0);
    b.SetRow(1, b_row1);
    b.SetRow(2, b_row2);
    b.SetRow(3, b_row3);

    const int w = 12;
    const char* delim = "  ";
    c1.SetOstream(w, delim);
    c2.SetOstream(w, delim);
    c3.SetOstream(w, delim);
    a.SetOstream(w, delim);
    b.SetOstream(w, delim);
}
