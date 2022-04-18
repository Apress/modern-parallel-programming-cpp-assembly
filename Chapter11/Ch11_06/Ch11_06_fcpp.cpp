//------------------------------------------------
//               Ch11_06_fcpp.cpp
//------------------------------------------------

#include "Ch11_06.h"

int SumElementsI32_Cpp(const int* x, size_t n)
{
    int sum = 0;

    for (size_t i = 0; i < n; i++)
        sum += x[i];

    return sum;
}
