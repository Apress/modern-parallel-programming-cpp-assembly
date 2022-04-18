//------------------------------------------------
//               MT.h
//------------------------------------------------

#pragma once
#include <vector>
#include <random>
#include <cmath>

// This namespace contain miscellaneous template functions.

namespace MT
{
    template <typename T> void FillArray(T* x, size_t n, int min_val, int max_val, unsigned int rng_seed, bool exclude_zero = false)
    {
        // Note: Same seed value generates different sequences on Windows and Linux.
        std::mt19937 rng {rng_seed};
        std::uniform_int_distribution<int> dist {min_val, max_val};

        if (exclude_zero)
        {
            for (size_t i = 0; i < n; i++)
            {
                int val;

                while ((val = dist(rng)) == 0) {}
                x[i] = (T)val;
            }
        }
        else
        {
            for (size_t i = 0; i < n; i++)
                x[i] = (T)dist(rng);
        }
    }

    template <typename T> void FillMatrix(T* x, size_t nrows, size_t ncols, int min_val, int max_val, unsigned int rng_seed, bool exclude_zero = false)
    {
        FillArray(x, nrows * ncols, min_val, max_val, rng_seed, exclude_zero);
    }

    template <typename T> void FillArrayFP(T* x, size_t n, T min_val, T max_val, unsigned int rng_seed)
    {
        // Note: 'dist' uses hard-coded double instead of T to force generation
        // of same sequences for both float and double arrays.
        std::mt19937 rng {rng_seed};
        std::uniform_real_distribution<double> dist {(double)min_val, (double)max_val};

        for (size_t i = 0; i < n; i++)
            x[i] = (T)dist(rng);
    }

    template <typename T> void FillMatrixFP(T* x, size_t nrows, size_t ncols, T min_val, T max_val, unsigned int rng_seed)
    {
        FillArrayFP(x, nrows * ncols, min_val, max_val, rng_seed);
    }

    template <typename T> bool CompareArraysFP(const T* a1, const T* a2, size_t n, T epsilon)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (fabs(a1[i] - a2[i]) > epsilon)
                return false;
        }

        return true;
    }

    template <typename T> bool CompareVectorsFP(const std::vector<T>& v1, const std::vector<T>& v2, T epsilon)
    {
        if (v1.size() != v2.size())
            return false;

        return CompareArraysFP(v1.data(), v2.data(), v1.size(), epsilon);
    }
};
