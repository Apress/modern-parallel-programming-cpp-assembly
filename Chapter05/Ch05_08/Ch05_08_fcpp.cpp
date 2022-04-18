//------------------------------------------------
//               Ch05_08_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <vector>
#include <immintrin.h>
#include "Ch05_08.h"
#include "MatrixF32.h"

bool MatrixInvF32_Cpp(MatrixF32& a_inv, const MatrixF32& a, float epsilon)
{
    size_t n = a.GetNumRows();

    if (n != a.GetNumCols())
        throw std::runtime_error("MatrixInvF32_Cpp() - non-square matrix");

    if (n != a_inv.GetNumRows() || n != a_inv.GetNumCols())
        throw std::runtime_error("MatrixInvF32_Cpp() - non-conforming matrices");

    // Calculate matrix products and trace values
    std::vector<float> t(n + 1);
    std::vector<MatrixF32> mats(n + 1);

    mats[0] = MatrixF32::I(n);
    mats[1] = a;
    t[1] = mats[1].Trace();

    for (size_t i = 2; i <= n; i++)
    {
        mats[i] = mats[i - 1] * a;
        t[i] = mats[i].Trace();
    }

    // Calculate characteristic equation coefficients
    std::vector<float> c(n + 1);
    c[0] = 1;
    c[1] = -t[1];
 
    for (size_t i = 2; i <= n; i++)
    {
        size_t j = 1;
        size_t k = i - 1;
        float sum = 0.0f;

        for (; j < i; j++)
        {
            sum += c[k] * t[j];
            k -= 1;
        }

        sum += t[j];
        c[i] = (-1.0f / i) * sum;
    }

    bool is_singular = (fabs(c[n]) < epsilon) ? true : false;

    if (!is_singular)
    {
        // Matrix a is non-singular, calculate the inverse
        a_inv = mats[n - 1] * c[0];
        size_t i = 1;
        size_t k = n - 2;

        for (; i <= n - 1; i++)
        {
            a_inv = a_inv + mats[k] * c[i];
            k -= 1;
        }

        MatrixF32::MulScalar(a_inv, a_inv, -1.0f / c[i]);
    }

    return is_singular;
}

bool MatrixInvF32_Iavx2(MatrixF32& a_inv, const MatrixF32& a, float epsilon)
{
    size_t n = a.GetNumRows();

    if (n != a.GetNumCols())
        throw std::runtime_error("MatrixInvF32_Iavx2() - non-square matrix");

    if (n != a_inv.GetNumRows() || n != a_inv.GetNumCols())
        throw std::runtime_error("MatrixInvF32_Iavx2() - non-conforming matrices");

    MatrixF32 temp1(n, n);

    // Calculate matrix products and trace values
    std::vector<float> t(n + 1);
    std::vector<MatrixF32> mats(n + 1);

    mats[0] = MatrixF32::I(n);
    mats[1] = a;
    t[1] = mats[1].Trace();

    for (size_t i = 2; i <= n; i++)
    {
//@@    mats[i] = mats[i - 1] * a;
        mats[i] = MatrixMulF32_Iavx2(mats[i - 1], a);
        t[i] = mats[i].Trace();
    }

    // Calculate characteristic equation coefficients
    std::vector<float> c(n + 1);
    c[0] = 1;
    c[1] = -t[1];
 
    for (size_t i = 2; i <= n; i++)
    {
        size_t j = 1;
        size_t k = i - 1;
        float sum = 0.0f;

        for (; j < i; j++)
        {
            sum += c[k] * t[j];
            k -= 1;
        }

        sum += t[j];
        c[i] = (-1.0f / i) * sum;
    }

    bool is_singular = (fabs(c[n]) < epsilon) ? true : false;

    if (!is_singular)
    {
        // Matrix a is non-singular, calculate the inverse
        a_inv = mats[n - 1] * c[0];
        size_t i = 1;
        size_t k = n - 2;

        for (; i <= n - 1; i++)
        {
//@@        a_inv = a_inv + mats[k] * c[i];
            MatrixMulScalarF32_Iavx2(temp1, mats[k], c[i]);
            a_inv = MatrixAddF32_Iavx2(a_inv, temp1);
            k -= 1;
        }

//@@    MatrixF32::MulScalar(a_inv, a_inv, -1.0f / c[i]);
        MatrixMulScalarF32_Iavx2(a_inv, a_inv, -1.0f / c[i]);
    }

    return is_singular;
}
