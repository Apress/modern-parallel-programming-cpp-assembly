//------------------------------------------------
//               Ch11_04.cpp
//------------------------------------------------

#include <iostream>
#include <cstdint>
#include "Ch11_04.h"

static void CalcResultI64(void);
static void CalcResultU64(void);

int main()
{
    CalcResultI64();
    CalcResultU64();
    return 0;
}

static void CalcResultI64(void)
{
    int8_t a = 2;
    int16_t b = -3;
    int32_t c = 8;
    int64_t d = 4;
    int8_t e = 3;
    int16_t f = -7;
    int32_t g = -5;
    int64_t h = 10;

    // Calculate (a * b * c * d) + (e * f * g * h)
    int64_t result1 = ((int64_t)a * b * c * d) + ((int64_t)e * f * g * h);
    int64_t result2 = CalcResultI64_A(a, b, c, d, e, f, g, h);

    std::cout << "\n----- Results for CalcResultI64 -----\n";
    std::cout << "a = " << (int)a << ", b = " << b << ", c = " << c << ' ';
    std::cout << "d = " << d << ", e = " << (int)e << ", f = " << f << ' ';
    std::cout << "g = " << g << ", h = " << h << '\n';
    std::cout << "result1 = " << result1 << '\n';
    std::cout << "result2 = " << result2 << '\n';
}

static void CalcResultU64(void)
{
    uint8_t a = 12;
    uint16_t b = 17;
    uint32_t c = 71000000;
    uint64_t d = 90000000000;
    uint8_t e = 101;
    uint16_t f = 37;
    uint32_t g = 25;
    uint64_t h = 5;
    uint64_t quo1, rem1;
    uint64_t quo2, rem2;

    quo1 = ((uint64_t)a + b + c + d) / ((uint64_t)e + f + g + h);
    rem1 = ((uint64_t)a + b + c + d) % ((uint64_t)e + f + g + h);
    CalcResultU64_A(a, b, c, d, e, f, g, h, &quo2, &rem2);

    std::cout << "\n----- Results for CalcResultU64 -----\n";
    std::cout << "a = " << (unsigned)a << ", b = " << b << ", c = " << c << ' ';
    std::cout << "d = " << d << ", e = " << (unsigned)e << ", f = " << f << ' ';
    std::cout << "g = " << g << ", h = " << h << '\n';
    std::cout << "quo1 = " << quo1 << ", rem1 = " << rem1 << '\n';
    std::cout << "quo2 = " << quo2 << ", rem2 = " << rem2 << '\n';
}
