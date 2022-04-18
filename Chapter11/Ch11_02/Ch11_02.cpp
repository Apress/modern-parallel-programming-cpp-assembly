//------------------------------------------------
//               Ch11_02.cpp
//------------------------------------------------

#include <iostream>
#include <cstdint>
#include "Ch11_02.h"

static void MulI32(void);
static void MulU64(void);

int main()
{
    MulI32();
    MulU64();
    return 0;
}

static void MulI32(void)
{
    int32_t a = 10;
    int32_t b = -20;
    int32_t c = 30;
    int32_t d = MulI32_A(a, b, c);

    DisplayResultsMulI32(a, b, c, d);
}

static void MulU64(void)
{
    uint64_t a = 10;
    uint64_t b = 20;
    uint64_t c = 1000000000;
    uint64_t d = MulU64_A(a, b, c);

    DisplayResultsMulU64(a, b, c, d);
}
