//------------------------------------------------
//               Ch09_02.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include "Ch09_02.h"

static void ConvertRectToPolar(void);
static void ConvertPolarToRect(void);

int main()
{
    try
    {
        ConvertRectToPolar();
        ConvertPolarToRect();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch09_02 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void ConvertRectToPolar(void)
{
    const size_t n = 19;
    std::vector<float> x(n), y(n);
    std::vector<float> r1(n), a1(n);
    std::vector<float> r2(n), a2(n);

    FillVectorsRect(x, y);
    ConvertRectToPolarF32_Cpp(r1, a1, x, y);
    ConvertRectToPolarF32_Iavx(r2, a2, x, y);

    size_t w = 10;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n----- Results for ConvertRectToPolar -----\n";

    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::setw(4) << i << ": ";
        std::cout << std::setw(w) << x[i] << ", ";
        std::cout << std::setw(w) << y[i] << " | ";
        std::cout << std::setw(w) << r1[i] << ", ";
        std::cout << std::setw(w) << a1[i] << " | ";
        std::cout << std::setw(w) << r2[i] << ", ";
        std::cout << std::setw(w) << a2[i] << '\n';
    }

    if (!CompareResults(r1, r2) || !CompareResults(a1, a2))
        throw std::runtime_error("CompareResults() failed");
}

static void ConvertPolarToRect(void)
{
    const size_t n = 19;
    std::vector<float> r(n), a(n);
    std::vector<float> x1(n), y1(n);
    std::vector<float> x2(n), y2(n);

    FillVectorsPolar(r, a);
    ConvertPolarToRectF32_Cpp(x1, y1, r, a);
    ConvertPolarToRectF32_Iavx(x2, y2, r, a);

    size_t w = 10;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n----- Results for ConvertPolarToRect -----\n";

    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::setw(4) << i << ": ";
        std::cout << std::setw(w) << r[i] << ", ";
        std::cout << std::setw(w) << a[i] << " | ";
        std::cout << std::setw(w) << x1[i] << ", ";
        std::cout << std::setw(w) << y1[i] << " | ";
        std::cout << std::setw(w) << x2[i] << ", ";
        std::cout << std::setw(w) << y2[i] << '\n';
    }

    if (!CompareResults(x1, x2) || !CompareResults(y1, y2))
        throw std::runtime_error("CompareResults() failed");
}
