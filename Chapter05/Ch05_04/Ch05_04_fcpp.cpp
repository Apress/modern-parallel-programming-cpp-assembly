//------------------------------------------------
//               Ch05_04_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch05_04.h"

void MatrixMul4x4F32_Cpp(MatrixF32& c, const MatrixF32& a, const MatrixF32& b)
{
    MatrixF32::Mul4x4(c, a, b);
}

void MatrixMul4x4F32_Iavx2(MatrixF32& c, const MatrixF32& a, const MatrixF32& b)
{
    const float* aa = a.Data();
    const float* bb = b.Data();
    float* cc = c.Data();

    // Load rows of matrix b
    __m128 b_row0 = _mm_load_ps(&bb[0]);
    __m128 b_row1 = _mm_load_ps(&bb[4]);
    __m128 b_row2 = _mm_load_ps(&bb[8]);
    __m128 b_row3 = _mm_load_ps(&bb[12]);

    // Calculate c_row0
    __m128 a_00 = _mm_broadcast_ss(&aa[0]);         // a[0][0]
    __m128 a_01 = _mm_broadcast_ss(&aa[1]);         // a[0][1]
    __m128 a_02 = _mm_broadcast_ss(&aa[2]);         // a[0][2]
    __m128 a_03 = _mm_broadcast_ss(&aa[3]);         // a[0][3]

    __m128 c_row0 = _mm_mul_ps(a_00, b_row0);
    c_row0 = _mm_fmadd_ps(a_01, b_row1, c_row0);
    c_row0 = _mm_fmadd_ps(a_02, b_row2, c_row0);
    c_row0 = _mm_fmadd_ps(a_03, b_row3, c_row0);
    _mm_store_ps(&cc[0], c_row0);

    // Calculate c_row1
    __m128 a_10 = _mm_broadcast_ss(&aa[4]);         // a[1][0]
    __m128 a_11 = _mm_broadcast_ss(&aa[5]);         // a[1][1]
    __m128 a_12 = _mm_broadcast_ss(&aa[6]);         // a[1][2]
    __m128 a_13 = _mm_broadcast_ss(&aa[7]);         // a[1][3]

    __m128 c_row1 = _mm_mul_ps(a_10, b_row0);
    c_row1 = _mm_fmadd_ps(a_11, b_row1, c_row1);
    c_row1 = _mm_fmadd_ps(a_12, b_row2, c_row1);
    c_row1 = _mm_fmadd_ps(a_13, b_row3, c_row1);
    _mm_store_ps(&cc[4], c_row1);

    // Calculate c_row2
    __m128 a_20 = _mm_broadcast_ss(&aa[8]);         // a[2][0]
    __m128 a_21 = _mm_broadcast_ss(&aa[9]);         // a[2][1]
    __m128 a_22 = _mm_broadcast_ss(&aa[10]);        // a[2][2]
    __m128 a_23 = _mm_broadcast_ss(&aa[11]);        // a[2][3]

    __m128 c_row2 = _mm_mul_ps(a_20, b_row0);
    c_row2 = _mm_fmadd_ps(a_21, b_row1, c_row2);
    c_row2 = _mm_fmadd_ps(a_22, b_row2, c_row2);
    c_row2 = _mm_fmadd_ps(a_23, b_row3, c_row2);
    _mm_store_ps(&cc[8], c_row2);

    // Calculate c_row3
    __m128 a_30 = _mm_broadcast_ss(&aa[12]);        // a[3][0]
    __m128 a_31 = _mm_broadcast_ss(&aa[13]);        // a[3][1]
    __m128 a_32 = _mm_broadcast_ss(&aa[14]);        // a[3][2]
    __m128 a_33 = _mm_broadcast_ss(&aa[15]);        // a[3][3]

    __m128 c_row3 = _mm_mul_ps(a_30, b_row0);
    c_row3 = _mm_fmadd_ps(a_31, b_row1, c_row3);
    c_row3 = _mm_fmadd_ps(a_32, b_row2, c_row3);
    c_row3 = _mm_fmadd_ps(a_33, b_row3, c_row3);
    _mm_store_ps(&cc[12], c_row3);
}
