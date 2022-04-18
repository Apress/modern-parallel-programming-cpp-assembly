//------------------------------------------------
//               Ch18_03.h
//------------------------------------------------

#pragma once
#include <vector>
#include "MatrixF64.h"

// Covariance matrix data
struct CMD
{
    MatrixF64 m_X;
    MatrixF64 m_CovMat;
    std::vector<double> m_VarMeans;

    CMD(size_t n_vars, size_t n_obvs) :
        m_X(n_vars, n_obvs), m_CovMat(n_vars, n_vars), m_VarMeans(n_vars) { }
};

// Ch18_03_fcpp.cpp
extern void CalcCovMatF64_Cpp(CMD& cmd);
extern void CalcCovMatF64_Aavx512(CMD& cmd);

// Ch18_03_fasm.asm
extern "C" void CalcCovMatF64_Aavx512(double* cov_mat, double* var_means, const double* x, size_t n_vars, size_t n_obs);

// Ch18_03_misc.cpp
extern bool CheckArgs(const CMD& cmd);
extern bool CompareResults(CMD& cmd1, CMD& cmd2);
extern void InitCMD(CMD& cmd1, CMD& cmd2);
