//------------------------------------------------
//               Ch05_05_fcpp.cpp
//------------------------------------------------

#include <immintrin.h>
#include "Ch05_05.h"

void MatrixMul4x4F64_Cpp(MatrixF64& c, const MatrixF64& a, const MatrixF64& b)
{
    MatrixF64::Mul4x4(c, a, b);
}

void MatrixMul4x4F64_Iavx2(MatrixF64& c, const MatrixF64& a, const MatrixF64& b)
{
    const double* aa = a.Data();
    const double* bb = b.Data();
    double* cc = c.Data();

    // Load rows of matrix b
    __m256d b_row0 = _mm256_load_pd(&bb[0]);
    __m256d b_row1 = _mm256_load_pd(&bb[4]);
    __m256d b_row2 = _mm256_load_pd(&bb[8]);
    __m256d b_row3 = _mm256_load_pd(&bb[12]);

    // Calculate c_row0
    __m256d a_00 = _mm256_broadcast_sd(&aa[0]);         // a[0][0]
    __m256d a_01 = _mm256_broadcast_sd(&aa[1]);         // a[0][1]
    __m256d a_02 = _mm256_broadcast_sd(&aa[2]);         // a[0][2]
    __m256d a_03 = _mm256_broadcast_sd(&aa[3]);         // a[0][3]

    __m256d c_row0 = _mm256_mul_pd(a_00, b_row0);
    c_row0 = _mm256_fmadd_pd(a_01, b_row1, c_row0);
    c_row0 = _mm256_fmadd_pd(a_02, b_row2, c_row0);
    c_row0 = _mm256_fmadd_pd(a_03, b_row3, c_row0);
    _mm256_store_pd(&cc[0], c_row0);

    // Calculate c_row1
    __m256d a_10 = _mm256_broadcast_sd(&aa[4]);         // a[1][0]
    __m256d a_11 = _mm256_broadcast_sd(&aa[5]);         // a[1][1]
    __m256d a_12 = _mm256_broadcast_sd(&aa[6]);         // a[1][2]
    __m256d a_13 = _mm256_broadcast_sd(&aa[7]);         // a[1][3]

    __m256d c_row1 = _mm256_mul_pd(a_10, b_row0);
    c_row1 = _mm256_fmadd_pd(a_11, b_row1, c_row1);
    c_row1 = _mm256_fmadd_pd(a_12, b_row2, c_row1);
    c_row1 = _mm256_fmadd_pd(a_13, b_row3, c_row1);
    _mm256_store_pd(&cc[4], c_row1);

    // Calculate c_row2
    __m256d a_20 = _mm256_broadcast_sd(&aa[8]);         // a[2][0]
    __m256d a_21 = _mm256_broadcast_sd(&aa[9]);         // a[2][1]
    __m256d a_22 = _mm256_broadcast_sd(&aa[10]);        // a[2][2]
    __m256d a_23 = _mm256_broadcast_sd(&aa[11]);        // a[2][3]

    __m256d c_row2 = _mm256_mul_pd(a_20, b_row0);
    c_row2 = _mm256_fmadd_pd(a_21, b_row1, c_row2);
    c_row2 = _mm256_fmadd_pd(a_22, b_row2, c_row2);
    c_row2 = _mm256_fmadd_pd(a_23, b_row3, c_row2);
    _mm256_store_pd(&cc[8], c_row2);

    // Calculate c_row3
    __m256d a_30 = _mm256_broadcast_sd(&aa[12]);        // a[3][0]
    __m256d a_31 = _mm256_broadcast_sd(&aa[13]);        // a[3][1]
    __m256d a_32 = _mm256_broadcast_sd(&aa[14]);        // a[3][2]
    __m256d a_33 = _mm256_broadcast_sd(&aa[15]);        // a[3][3]

    __m256d c_row3 = _mm256_mul_pd(a_30, b_row0);
    c_row3 = _mm256_fmadd_pd(a_31, b_row1, c_row3);
    c_row3 = _mm256_fmadd_pd(a_32, b_row2, c_row3);
    c_row3 = _mm256_fmadd_pd(a_33, b_row3, c_row3);
    _mm256_store_pd(&cc[12], c_row3);
}
