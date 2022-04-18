//------------------------------------------------
//               Ch09_03.h
//------------------------------------------------

#pragma once
#include <vector>

// Ch09_03_fcpp.cpp
extern void CalcBSA_F64_Cpp(std::vector<double>& bsa, const std::vector<double>& ht,
    const std::vector<double>& wt);
extern void CalcBSA_F64_Iavx(std::vector<double>& bsa, const std::vector<double>& ht,
    const std::vector<double>& wt);

// Ch09_03_misc.cpp
extern bool CheckArgs(const std::vector<double>& bsa,
    const std::vector<double>& ht, const std::vector<double>& wt);
extern bool CompareResults(const std::vector<double>& bsa1,
    const std::vector<double>& bsa2);
extern void FillHeightWeightVectors(std::vector<double>& ht,
    std::vector<double>& wt);

// Ch09_03_bm.cpp
void CalcBSA_bm(void);
