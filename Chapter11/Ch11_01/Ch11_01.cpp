//------------------------------------------------
//               Ch11_01.cpp
//------------------------------------------------

#include <iostream>
#include "Ch11_01.h"

static void AddI32(void);
static void SubI64(void);

int main()
{
    AddI32();
    SubI64();
    return 0;
}

static void AddI32(void)
{
    int a = 10;
    int b = 20;
    int c = 30;
    int d = AddI32_A(a, b, c);

    DisplayResultsAddI32(a, b, c, d);
}

static void SubI64(void)
{
    long long a = 10;
    long long b = 20;
    long long c = 30;
    long long d = SubI64_A(a, b, c);

    DisplayResultsSubI64(a, b, c, d);
}
