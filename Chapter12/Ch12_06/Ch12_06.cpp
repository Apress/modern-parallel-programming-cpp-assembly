//------------------------------------------------
//               Ch12_06.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Ch12_06.h"

static void SumIntegers(void);

int main()
{
    SumIntegers();
    return 0;
}

static void SumIntegers(void)
{
    int8_t a = 10, e = -20;
    int16_t b = -200, f = 400;
    int32_t c = -300, g = -600;
    int64_t d = 4000, h = -8000;

    int64_t sum = SumIntegers_A(a, b, c, d, e, f, g, h);

    const char nl = '\n';
    const size_t w = 7;
    std::cout << "----- Results for SumIntegers_A ----- \n";
    std::cout << "a:   " << std::setw(w) << (int)a << nl;
    std::cout << "b:   " << std::setw(w) << b << nl;
    std::cout << "c:   " << std::setw(w) << c << nl;
    std::cout << "d:   " << std::setw(w) << d << nl;
    std::cout << "e:   " << std::setw(w) << (int)e << nl;
    std::cout << "f:   " << std::setw(w) << f << nl;
    std::cout << "g:   " << std::setw(w) << g << nl;
    std::cout << "h:   " << std::setw(w) << h << nl;
    std::cout << "sum: " << std::setw(w) << sum << nl;
}
