//------------------------------------------------
//               Ch11_03.cpp
//------------------------------------------------

#include <iostream>
#include <cstdint>
#include "Ch11_03.h"

static void DivI32(void);
static void DivU64(void);

int main()
{
    DivI32();
    DivU64();
    return 0;
}

static void DivI32(void)
{
    const size_t n = 4;
    const int32_t a[n] = { 47, -291, 19, 247 };
    const int32_t b[n] = { 13, 7, 0, 85 };

    std::cout << "----- Results for DivI32() -----\n";

    for (size_t i = 0; i < n; i++)
    {
        int32_t quo = 0, rem = 0;
        int32_t rc = DivI32_A(a[i], b[i], &quo, &rem);

        DisplayResultsDivI32(i, rc, a[i], b[i], quo, rem);
    }
}

static void DivU64(void)
{
    const size_t n = 4;
    const uint64_t a[4] = { 147, 300, 2000, 9876543210 };
    const uint64_t b[4] = { 17, 15, 0, 1011 };

    std::cout << "----- Results for Div64U() -----\n";

    for (size_t i = 0; i < n; i++)
    {
        uint64_t quo = 0, rem = 0;
        int32_t rc = DivU64_A(a[i], b[i], &quo, &rem);

        DisplayResultsDivU64(i, rc, a[i], b[i], quo, rem);
    }
}
