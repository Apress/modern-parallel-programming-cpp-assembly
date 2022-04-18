//------------------------------------------------
//               Ch05_09_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <vector>
#include <immintrin.h>
#include "Ch05_09.h"
#include "MatrixF64.h"

bool MatrixInvF64_Cpp(MatrixF64& a_inv, const MatrixF64& a, double epsilon)
{
    size_t n = a.GetNumRows();

    if (n != a.GetNumCols())
        throw std::runtime_error("MatrixInvF64_Cpp() - non-square matrix");

    if (n != a_inv.GetNumRows() || n != a_inv.GetNumCols())
        throw std::runtime_error("MatrixInvF64_Cpp() - non-conforming matrices");

    // Calculate matrix products and trace values
    std::vector<double> t(n + 1);
    std::vector<MatrixF64> mats(n + 1);

    mats[0] = MatrixF64::I(n);
    mats[1] = a;
    t[1] = mats[1].Trace();

    for (size_t i = 2; i <= n; i++)
    {
        mats[i] = mats[i - 1] * a;
        t[i] = mats[i].Trace();
    }

    // Calculate characteristic equation coefficients
    std::vector<double> c(n + 1);
    c[0] = 1;
    c[1] = -t[1];
 
    for (size_t i = 2; i <= n; i++)
    {
        size_t j = 1;
        size_t k = i - 1;
        double sum = 0.0;

        for (; j < i; j++)
        {
            sum += c[k] * t[j];
            k -= 1;
        }

        sum += t[j];
        c[i] = (-1.0 / i) * sum;
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

        MatrixF64::MulScalar(a_inv, a_inv, -1.0 / c[i]);
    }

    return is_singular;
}

bool MatrixInvF64_Iavx2(MatrixF64& a_inv, const MatrixF64& a, double epsilon)
{
    size_t n = a.GetNumRows();

    if (n != a.GetNumCols())
        throw std::runtime_error("MatrixInvF64_Iavx2() - non-square matrix");

    if (n != a_inv.GetNumRows() || n != a_inv.GetNumCols())
        throw std::runtime_error("MatrixInvF64_Iavx2() - non-conforming matrices");

    MatrixF64 temp1(n, n);

    // Calculate matrix products and trace values
    std::vector<double> t(n + 1);
    std::vector<MatrixF64> mats(n + 1);

    mats[0] = MatrixF64::I(n);
    mats[1] = a;
    t[1] = mats[1].Trace();

    for (size_t i = 2; i <= n; i++)
    {
//@@    mats[i] = mats[i - 1] * a;
        mats[i] = MatrixMulF64_Iavx2(mats[i - 1], a);
        t[i] = mats[i].Trace();
    }

    // Calculate characteristic equation coefficients
    std::vector<double> c(n + 1);
    c[0] = 1;
    c[1] = -t[1];
 
    for (size_t i = 2; i <= n; i++)
    {
        size_t j = 1;
        size_t k = i - 1;
        double sum = 0.0;

        for (; j < i; j++)
        {
            sum += c[k] * t[j];
            k -= 1;
        }

        sum += t[j];
        c[i] = (-1.0 / i) * sum;
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
            MatrixMulScalarF64_Iavx2(temp1, mats[k], c[i]);
            a_inv = MatrixAddF64_Iavx2(a_inv, temp1);
            k -= 1;
        }

//@@    MatrixF64::MulScalar(a_inv, a_inv, -1.0 / c[i]);
        MatrixMulScalarF64_Iavx2(a_inv, a_inv, -1.0 / c[i]);
    }

    return is_singular;
}
