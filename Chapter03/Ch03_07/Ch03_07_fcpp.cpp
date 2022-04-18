//------------------------------------------------
//               Ch03_07_fcpp.cpp
//------------------------------------------------

#include <cmath>
#include <immintrin.h>
#include "Ch03_07.h"

bool CalcDistancesF64_Cpp(PointArrays& pa)
{
    if (!CheckArgs(pa))
        return false;

    size_t num_points = pa.NumPoints;

    for (size_t i = 0; i < num_points; i++)
    {
        double temp1 = pa.X1[i] - pa.X2[i];
        double temp2 = pa.Y1[i] - pa.Y2[i];
        pa.Dist1[i] = sqrt(temp1 * temp1 + temp2 * temp2);
    }

    return true;
}

void CompareDistancesF64_Cpp(PointArrays& pa, double cmp_val)
{
    size_t num_points = pa.NumPoints;

    for (size_t i = 0; i < num_points; i++)
    {
        double temp1 = pa.Dist1[i];
        double temp2 = (temp1 >= cmp_val) ? temp1 * -2.0 : temp1;
        pa.DistCmp1[i] = temp2;
    }
}

bool CalcDistancesF64_Iavx(PointArrays& pa)
{
    if (!CheckArgs(pa))
        return false;

    size_t i = 0;
    size_t num_points = pa.NumPoints;
    const size_t num_simd_elements = 4;

    for (; num_points - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256d x1_vals = _mm256_load_pd(&pa.X1[i]);
        __m256d y1_vals = _mm256_load_pd(&pa.Y1[i]);
        __m256d x2_vals = _mm256_load_pd(&pa.X2[i]);
        __m256d y2_vals = _mm256_load_pd(&pa.Y2[i]);

        __m256d temp_x = _mm256_sub_pd(x1_vals, x2_vals);
        __m256d temp_y = _mm256_sub_pd(y1_vals, y2_vals);
        __m256d temp_xx = _mm256_mul_pd(temp_x, temp_x);
        __m256d temp_yy = _mm256_mul_pd(temp_y, temp_y);
        __m256d temp_sum = _mm256_add_pd(temp_xx, temp_yy);
        __m256d temp_dist = _mm256_sqrt_pd(temp_sum);

        _mm256_store_pd(&pa.Dist2[i], temp_dist);
    }

    for (; i < num_points; i++)
    {
        double temp1 = pa.X1[i] - pa.X2[i];
        double temp2 = pa.Y1[i] - pa.Y2[i];
        pa.Dist2[i] = sqrt(temp1 * temp1 + temp2 * temp2);
    }

    return true;
}

void CompareDistancesF64_Iavx(PointArrays& pa, double cmp_val)
{
    size_t i = 0;
    size_t num_points = pa.NumPoints;
    const size_t num_simd_elements = 4;
    const double minus2 = -2.0;

    __m256d cmp_vals = _mm256_broadcast_sd(&cmp_val);
    __m256d packed_minus2 = _mm256_broadcast_sd(&minus2);

    for (; num_points - i >= num_simd_elements; i += num_simd_elements)
    {
        __m256d dist2_vals = _mm256_load_pd(&pa.Dist2[i]);

        // Elements in cmp_mask contain 0xFFFFFFFFFFFFFFFF or 0x0000000000000000
        __m256d cmp_mask = _mm256_cmp_pd(dist2_vals, cmp_vals, _CMP_GE_OQ);

        // Elements in temp1 contain -2.0 or 0.0
        __m256d temp1 = _mm256_and_pd(cmp_mask, packed_minus2);

        // Elements in temp2 contain -2.0 * dist2_vals or 0.0
        __m256d temp2 = _mm256_mul_pd(temp1, dist2_vals);

        // Elements in temp3 contain 0.0 or dist2_vals
        __m256d temp3 = _mm256_andnot_pd(cmp_mask, dist2_vals);

        // Elements in temp4 contain -2.0 * dist2_vals or dist2_vals
        __m256d temp4 = _mm256_or_pd(temp2, temp3);

        _mm256_store_pd(&pa.DistCmp2[i], temp4);
    }

    for (; i < num_points; i++)
    {
        double temp1 = pa.Dist2[i];
        double temp2 = (temp1 >= cmp_val) ? temp1 * -2.0 : temp1;
        pa.DistCmp2[i] = temp2;
    }
}
