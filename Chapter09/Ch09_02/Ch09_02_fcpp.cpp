//------------------------------------------------
//               Ch09_02_fcpp.cpp
//------------------------------------------------

#include <iostream>
#include <stdexcept>
#include <immintrin.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Ch09_02.h"
#include "SimdMath.h"

const float c_DegToRad = (float)(M_PI / 180.0);
const float c_RadToDeg = (float)(180.0 / M_PI);

void ConvertRectToPolarF32_Cpp(std::vector<float>& r, std::vector<float>& a,
    const std::vector<float>& x, const std::vector<float>& y)
{
    if (!CheckArgs(r, a, x, y))
        throw std::runtime_error("ConvertRectToPolarF32_Cpp() - CheckArgs failed");

    size_t n = r.size();

    for (size_t i = 0; i < n; i++)
    {
        r[i] = sqrt(x[i] * x[i] + y[i] * y[i]);
        a[i] = atan2(y[i], x[i]) * c_RadToDeg; 
    }
}

void ConvertPolarToRectF32_Cpp(std::vector<float>& x, std::vector<float>& y,
    const std::vector<float>& r, const std::vector<float>& a)
{
    if (!CheckArgs(x, y, r, a))
        throw std::runtime_error("ConvertPolarToRectF32_Cpp() - CheckArgs failed");

    size_t n = x.size();

    for (size_t i = 0; i < n; i++)
    {
        x[i] = r[i] * cos(a[i] * c_DegToRad);
        y[i] = r[i] * sin(a[i] * c_DegToRad);
    }
}

void ConvertRectToPolarF32_Iavx(std::vector<float>& r, std::vector<float>& a,
    const std::vector<float>& x, const std::vector<float>& y)
{
    if (!CheckArgs(r, a, x, y))
        throw std::runtime_error("ConvertRectToPolarF32_Iavx() - CheckArgs failed");

    size_t n = r.size();

    __m256 rad_to_deg = _mm256_set1_ps(c_RadToDeg);

    size_t i = 0;
    const size_t num_simd_elements = 8;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256 x_vals = _mm256_loadu_ps(&x[i]);
        __m256 y_vals = _mm256_loadu_ps(&y[i]);
        __m256 x_vals2 = _mm256_mul_ps(x_vals, x_vals);
        __m256 y_vals2 = _mm256_mul_ps(y_vals, y_vals);

        __m256 temp = _mm256_add_ps(x_vals2, y_vals2);
        __m256 r_vals = _mm256_sqrt_ps(temp);
        _mm256_storeu_ps(&r[i], r_vals);

        __m256 a_vals_rad = atan2_f32x8(y_vals, x_vals);
        __m256 a_vals_deg = _mm256_mul_ps(a_vals_rad, rad_to_deg);
        _mm256_storeu_ps(&a[i], a_vals_deg);
    }

    for (; i < n; i++)
    {
        r[i] = sqrt(x[i] * x[i] + y[i] * y[i]);
        a[i] = atan2(y[i], x[i]) * c_RadToDeg; 
    }
}

void ConvertPolarToRectF32_Iavx(std::vector<float>& x, std::vector<float>& y,
    const std::vector<float>& r, const std::vector<float>& a)
{
    if (!CheckArgs(x, y, r, a))
        throw std::runtime_error("ConvertPolarToRectF32_Iavx() - CheckArgs failed");

    size_t n = x.size();

    __m256 deg_to_rad = _mm256_set1_ps(c_DegToRad);

    size_t i = 0;
    const size_t num_simd_elements = 8;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256 r_vals = _mm256_loadu_ps(&r[i]);
        __m256 a_vals_deg = _mm256_loadu_ps(&a[i]);
        __m256 a_vals_rad = _mm256_mul_ps(a_vals_deg, deg_to_rad);

        __m256 x_vals_temp = cos_f32x8(a_vals_rad);
        __m256 x_vals = _mm256_mul_ps(r_vals, x_vals_temp);
        _mm256_storeu_ps(&x[i], x_vals);

        __m256 y_vals_temp = sin_f32x8(a_vals_rad);
        __m256 y_vals = _mm256_mul_ps(r_vals, y_vals_temp);
        _mm256_storeu_ps(&y[i], y_vals);
    }

    for (; i < n; i++)
    {
        x[i] = r[i] * cos(a[i] * c_DegToRad);
        y[i] = r[i] * sin(a[i] * c_DegToRad);
    }
}
