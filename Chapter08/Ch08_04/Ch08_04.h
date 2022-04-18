//------------------------------------------------
//               Ch08_04.h
//------------------------------------------------

#pragma once
#include <vector>
#include "MatrixF64.h"

// Note: In this example, CMD stands for covariance matrix data
struct CMD
{
    MatrixF64 m_X;                      // Data matrix
    MatrixF64 m_CovMat;                 // Covariance matrix
    std::vector<double> m_VarMeans;     // Variable (row) means

    CMD(size_t n_vars, size_t n_obvs) :
        m_X(n_vars, n_obvs), m_CovMat(n_vars, n_vars), m_VarMeans(n_vars) { }
};

// Ch08_04_fcpp.cpp
extern void CalcCovMatF64_Cpp(CMD& cmd);
extern void CalcCovMatF64_Iavx512(CMD& cmd);

// Ch08_04_misc.cpp
extern bool CheckArgs(const CMD& cmd);
extern bool CompareResults(CMD& cmd1, CMD& cmd2);
extern void InitCMD(CMD& cmd1, CMD& cmd2);

// Ch08_04_misc2.cpp
extern void DisplayData(const CMD& cmd);
