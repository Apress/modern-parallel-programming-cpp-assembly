//------------------------------------------------
//               SimdMath.h
//------------------------------------------------

#if _MSC_VER >= 1921        // VS 2019 or later
#include <cmath>
#include <immintrin.h>
#elif defined(__GNUG__)
#include <cmath>
#include <immintrin.h>
#else
#error Unknown target in SimdMath.h
#endif

inline __m256 atan2_f32x8(__m256 y, __m256 x)
{
#if _MSC_VER >= 1921
    return _mm256_atan2_ps(y, x);
#endif

#if defined(__GNUG__)
    __m256 atan2_vals;
    for (size_t i = 0; i < 8; i++)
        atan2_vals[i] = atan2(y[i], x[i]);
    return atan2_vals;
#endif
}

inline __m256 cos_f32x8(__m256 x)
{
#if _MSC_VER >= 1921
    return _mm256_cos_ps(x);
#endif

#if defined(__GNUG__)
    __m256 cos_vals;
    for (size_t i = 0; i < 8; i++)
        cos_vals[i] = cos(x[i]);
    return cos_vals;
#endif
}

inline __m256d pow_f64x4(__m256d x, __m256d y)
{
#if _MSC_VER >= 1921
    return _mm256_pow_pd(x, y);
#endif

#if defined(__GNUG__)
    __m256d pow_vals;
    for (size_t i = 0; i < 4; i++)
        pow_vals[i] = pow(x[i], y[i]);
    return pow_vals;
#endif
}

inline __m256 sin_f32x8(__m256 x)
{
#if _MSC_VER >= 1921
    return _mm256_sin_ps(x);
#endif

#if defined(__GNUG__)
    __m256 sin_vals;
    for (size_t i = 0; i < 8; i++)
        sin_vals[i] = sin(x[i]);
    return sin_vals;
#endif
}
