//------------------------------------------------
//               Ch03_06_fcpp.cpp
//------------------------------------------------

#include <cmath>
#include <immintrin.h>
#include "Ch03_06.h"
#include "AlignedMem.h"

bool CalcDistancesF32_Cpp(PointArrays& pa)
{
    if (!CheckArgs(pa))
        return false;

    size_t num_points = pa.NumPoints;

    for (size_t i = 0; i < num_points; i++)
    {
        float temp1 = pa.X1[i] - pa.X2[i];
        float temp2 = pa.Y1[i] - pa.Y2[i];
        pa.Dist1[i] = sqrt(temp1 * temp1 + temp2 * temp2);
    }

    return true;
}

void CompareDistancesF32_Cpp(PointArrays& pa, float cmp_val)
{
    size_t num_points = pa.NumPoints;

    for (size_t i = 0; i < num_points; i++)
    {
        float temp1 = pa.Dist1[i];
        float temp2 = (temp1 >= cmp_val) ? temp1 * -2.0f : temp1;
        pa.DistCmp1[i] = temp2;
    }
}

bool CalcDistancesF32_Iavx(PointArrays& pa)
{
    if (!CheckArgs(pa))
        return false;

    size_t i = 0;
    size_t num_points = pa.NumPoints;
    const size_t num_simd_elements = 8;

    for (; num_points - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256 x1_vals = _mm256_load_ps(&pa.X1[i]);
        __m256 y1_vals = _mm256_load_ps(&pa.Y1[i]);
        __m256 x2_vals = _mm256_load_ps(&pa.X2[i]);
        __m256 y2_vals = _mm256_load_ps(&pa.Y2[i]);

        __m256 temp_x = _mm256_sub_ps(x1_vals, x2_vals);
        __m256 temp_y = _mm256_sub_ps(y1_vals, y2_vals);
        __m256 temp_xx = _mm256_mul_ps(temp_x, temp_x);
        __m256 temp_yy = _mm256_mul_ps(temp_y, temp_y);
        __m256 temp_sum = _mm256_add_ps(temp_xx, temp_yy);
        __m256 temp_dist = _mm256_sqrt_ps(temp_sum);

        _mm256_store_ps(&pa.Dist2[i], temp_dist);
    }

    for (; i < num_points; i++)
    {
        float temp1 = pa.X1[i] - pa.X2[i];
        float temp2 = pa.Y1[i] - pa.Y2[i];
        pa.Dist2[i] = sqrt(temp1 * temp1 + temp2 * temp2);
    }

    return true;
}

void CompareDistancesF32_Iavx(PointArrays& pa, float cmp_val)
{
    size_t i = 0;
    size_t num_points = pa.NumPoints;
    const size_t num_simd_elements = 8;
    const float minus2 = -2.0f;

    __m256 cmp_vals = _mm256_broadcast_ss(&cmp_val);
    __m256 packed_minus2 = _mm256_broadcast_ss(&minus2);

    for (; num_points - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256 dist2_vals = _mm256_load_ps(&pa.Dist2[i]);

        // Elements in cmp_mask contain 0xFFFFFFFF or 0x00000000
        __m256 cmp_mask = _mm256_cmp_ps(dist2_vals, cmp_vals, _CMP_GE_OQ);

        // Elements in temp1 contain -2.0 or 0.0
        __m256 temp1 = _mm256_and_ps(cmp_mask, packed_minus2);

        // Elements in temp2 contain -2.0 * dist2_vals or 0.0
        __m256 temp2 = _mm256_mul_ps(temp1, dist2_vals);

        // Elements in temp3 contain 0.0 or dist2_vals
        __m256 temp3 = _mm256_andnot_ps(cmp_mask, dist2_vals);

        // Elements in temp4 contain -2.0 * dist2_vals or dist2_vals
        __m256 temp4 = _mm256_or_ps(temp2, temp3);

        _mm256_store_ps(&pa.DistCmp2[i], temp4);
    }

    for (; i < num_points; i++)
    {
        float temp1 = pa.Dist2[i];
        float temp2 = (temp1 >= cmp_val) ? temp1 * -2.0f : temp1;
        pa.DistCmp2[i] = temp2;
    }
}
