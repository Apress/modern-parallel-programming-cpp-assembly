//------------------------------------------------
//               Ch11_06.cpp
//------------------------------------------------

#include <iostream>
#include <cstdint>
#include "Ch11_06.h"

static void SumElementsI32(void);

int main()
{
    SumElementsI32();
    return 0;
}

static void SumElementsI32(void)
{
    const size_t n = 20;
    int x[n];

    FillArray(x, n);

    int sum1 = SumElementsI32_Cpp(x, n);
    int sum2 = SumElementsI32_A(x, n);

    DisplayResults(x, n, sum1, sum2);
}