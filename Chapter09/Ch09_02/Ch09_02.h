//------------------------------------------------
//               Ch09_02.h
//------------------------------------------------

#pragma once
#include <vector>

// Ch09_02_fcpp.cpp
extern void ConvertRectToPolarF32_Cpp(std::vector<float>& r, std::vector<float>& a,
    const std::vector<float>& x, const std::vector<float>& y);
extern void ConvertRectToPolarF32_Iavx(std::vector<float>& r, std::vector<float>& a,
    const std::vector<float>& x, const std::vector<float>& y);
extern void ConvertPolarToRectF32_Cpp(std::vector<float>& x, std::vector<float>& y,
    const std::vector<float>& r, const std::vector<float>& a);
extern void ConvertPolarToRectF32_Iavx(std::vector<float>& x, std::vector<float>& y,
    const std::vector<float>& r, const std::vector<float>& a);

// Ch09_02_misc.cpp
extern bool CheckArgs(const std::vector<float>& v1, const std::vector<float>& v2,
    const std::vector<float>& v3, const std::vector<float>& v4);
extern bool CompareResults(const std::vector<float>& v1,
    const std::vector<float>& v2);
extern void FillVectorsRect(std::vector<float>& x, std::vector<float>& y);
extern void FillVectorsPolar(std::vector<float>& r, std::vector<float>& a);
