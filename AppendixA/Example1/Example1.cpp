//------------------------------------------------
//               Example1.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <immintrin.h>

static void CalcZ_Iavx(float* z, const float* x, const float* y, size_t n);
extern "C" void CalcZ_Aavx(float* z, const float* x, const float* y, size_t n);

int main()
{
    const size_t n = 19;
    float x[n], y[n], z1[n], z2[n];

    // Initialize the data arrays
    for (size_t i = 0; i < n; i++)
    {
        x[i] = i * 10.0f + 10.0f;
        y[i] = i * 1000.0f + 1000.0f;
        z1[i] = z2[i] = 0.0f;
    }

    // Exercise the SIMD calculating functions
    CalcZ_Iavx(z1, x, y, n);
    CalcZ_Aavx(z2, x, y, n);

    // Display the results
    const char nl = '\n';
    const size_t w = 10;
    std::cout << std::fixed << std::setprecision(1);

    std::cout << std::setw(w) << "i";
    std::cout << std::setw(w) << "x";
    std::cout << std::setw(w) << "y";
    std::cout << std::setw(w) << "z1";
    std::cout << std::setw(w) << "z2" << nl;
    std::cout << std::string(60, '-') << nl;

    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::setw(w) << i;
        std::cout << std::setw(w) << x[i];
        std::cout << std::setw(w) << y[i];
        std::cout << std::setw(w) << z1[i];
        std::cout << std::setw(w) << z2[i] << nl;
    }
}

void CalcZ_Iavx(float* z, const float* x, const float* y, size_t n)
{
    size_t i = 0;
    const size_t num_simd_elements = 8;

    for (; n - i >= num_simd_elements; i += num_simd_elements)
    {
        // Calculate z[i:i+7] = x[i:i+7] + y[i:i+7]
        __m256 x_vals = _mm256_loadu_ps(&x[i]);
        __m256 y_vals = _mm256_loadu_ps(&y[i]);
        __m256 z_vals = _mm256_add_ps(x_vals, y_vals);

        _mm256_storeu_ps(&z[i], z_vals);
    }

    // Calculate z[i] = x[i] + y[i] for any remaining elements
    for (; i < n; i += 1)
        z[i] = x[i] + y[i];
}
