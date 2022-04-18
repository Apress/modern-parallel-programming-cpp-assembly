//------------------------------------------------
//               Ch11_03_misc.cpp
//------------------------------------------------

#include <iostream>
#include "Ch11_03.h"

void DisplayResultsDivI32(size_t test_id, int rc, int32_t a,
    int32_t b, int32_t quo, int32_t rem)
{
    const char nl = '\n';
    std::cout << "Test #" << test_id << " | ";
    std::cout << "a: " << a << "  b: " << b << nl;

    if (rc != 0)
        std::cout << "quo: " << quo << "  rem: " << rem << nl;
    else
        std::cout << "quo: undefined  rem: undefined" << nl;

    std::cout << nl;
}

void DisplayResultsDivU64(size_t test_id, int rc, uint64_t a,
    uint64_t b, uint64_t quo, uint64_t rem)
{
    const char nl = '\n';
    std::cout << "Test #" << test_id << " | ";
    std::cout << "a: " << a << "  b: " << b << nl;

    if (rc != 0)
        std::cout << "quo: " << quo << "  rem: " << rem << nl;
    else
        std::cout << "quo: undefined  rem: undefined" << nl;

    std::cout << nl;
}
