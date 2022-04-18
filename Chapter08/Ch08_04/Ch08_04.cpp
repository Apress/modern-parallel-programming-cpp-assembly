//------------------------------------------------
//               Ch08_04.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch08_04.h"

static void CalcCovMatF64(void);

int main()
{
    try
    {
        CalcCovMatF64();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch08_04 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void CalcCovMatF64(void)
{
    const char nl = '\n';
    const size_t n_vars = 12;
    const size_t n_obvs = 111;

    CMD cmd1(n_vars, n_obvs);
    CMD cmd2(n_vars, n_obvs);
    InitCMD(cmd1, cmd2);

    // Calculate covariance  matrices
    CalcCovMatF64_Cpp(cmd1);
    CalcCovMatF64_Iavx512(cmd2);

    // Display results
    std::cout << std::fixed << std::setprecision(2);
    std::cout <<"Results for CalcCovMatF64\n";
    std::cout << "n_vars = " << n_vars << ", n_obvs = " << n_obvs << nl;

    if (n_vars <= 13)
    {
        std::cout << "Variable means\n";

        for (size_t i = 0; i < n_vars; i++)
        {
            std::cout << std::setw(4) << i << ": ";
            std::cout << std::setw(9) << cmd1.m_VarMeans[i] << " ";
            std::cout << std::setw(9) << cmd2.m_VarMeans[i] << nl;
        }

        std::cout << "\ncmd1.m_CovMat\n" << cmd1.m_CovMat << nl;
        std::cout << "\ncmd2.m_CovMat\n" << cmd2.m_CovMat << nl;
    }

    if (CompareResults(cmd1, cmd2))
        std::cout << "CompareResults - passed\n";
    else
        std::cout << "CompareResults - failed!\n";
}
