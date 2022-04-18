//------------------------------------------------
//               Ch19_01.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <vector>
#include "MatrixF32.h"

// Ch19_01_fcpp.cpp
extern void CalcRowStatsF32a_Iavx512(MatrixF32& x, std::vector<float>& row_means, std::vector<float>& row_sds);
extern void CalcRowStatsF32b_Iavx512(MatrixF32& x, std::vector<float>& row_means, std::vector<float>& row_sds);

// Ch19_01_fcpp2.cpp
extern void CalcRowStatsF32_Cpp(MatrixF32& x, std::vector<float>& row_means, std::vector<float>& row_sds);

// Ch19_01_misc.cpp
extern bool CheckArgs(const MatrixF32& x, const std::vector<float>& v1, const std::vector<float>& v2);
extern bool CompareResults(const std::vector<float>& v1, const std::vector<float>& v2);
extern void Init(MatrixF32& x);

extern void SaveResults(const char* bn, const MatrixF32& x,
    const std::vector<float>& row_means1, const std::vector<float>& row_means2, const std::vector<float>& row_means3,
    const std::vector<float>& row_sds1, const std::vector<float>& row_sds2, const std::vector<float>& row_sds3);

// Ch19_01_bm.cpp
extern void CalcRowStatsF32_bm(void);
