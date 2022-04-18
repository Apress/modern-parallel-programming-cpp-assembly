//------------------------------------------------
//               Ch11_08.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Ch11_08.h"

static void CopyArray(void);
static void FillArray(void);

int main()
{
    CopyArray();
    FillArray();
    return 0;
}

static void CopyArray(void)
{
    const size_t n = 10;
    const int32_t a[n] = {100, -200, 300, 400, -500, 600, 700, -800, 900, 1000};
    int32_t b[n] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    CopyArrayI32_A(b, a, n);

    std::cout << "\n----- Results for CopyArrayI32_A -----\n";

    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::setw(5) << i << ": ";
        std::cout << std::setw(5) << a[i] << " ";
        std::cout << std::setw(5) << b[i] << '\n';
    }
}

static void FillArray(void)
{
    const int32_t val = -7;
    const size_t n = 10;
    const int32_t a[n] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    FillArrayI32_A(a, val, n);

    std::cout << "\n----- Results for FillArrayI32_A -----\n";

    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::setw(5) << i << ": ";
        std::cout << std::setw(5) << a[i] << '\n';
    }
}

