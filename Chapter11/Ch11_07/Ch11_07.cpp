//------------------------------------------------
//               Ch11_07.cpp
//------------------------------------------------

#include <iostream>
#include <cstdint>
#include "Ch11_07.h"

static void SignedMinI32(void);
static void SignedMaxI32(void);

int main()
{
    SignedMinI32();
    SignedMaxI32();
    return 0;
}

static void SignedMinI32()
{
    const char nl = '\n';
    int a, b, c, smin1, smin2;

    // SignedMin examples
    a = 2; b = 15; c = 8;
    smin1 = SignedMin1_A(a, b, c);
    smin2 = SignedMin2_A(a, b, c);
    DisplayResult("SignedMin1_A", a, b, c, smin1);
    DisplayResult("SignedMin2_A", a, b, c, smin2);
    std::cout << nl;

    a = -3; b = -22; c = 28;
    smin1 = SignedMin1_A(a, b, c);
    smin2 = SignedMin2_A(a, b, c);
    DisplayResult("SignedMin1_A", a, b, c, smin1);
    DisplayResult("SignedMin2_A", a, b, c, smin2);
    std::cout << nl;

    a = 17; b = 37; c = -11;
    smin1 = SignedMin1_A(a, b, c);
    smin2 = SignedMin2_A(a, b, c);
    DisplayResult("SignedMin1_A", a, b, c, smin1);
    DisplayResult("SignedMin2_A", a, b, c, smin2);
    std::cout << nl;
}

static void SignedMaxI32()
{
    const char nl = '\n';
    int a, b, c, smax1, smax2;

    // SignedMax examples
    a = 10; b = 5; c = 3;
    smax1 = SignedMax1_A(a, b, c);
    smax2 = SignedMax2_A(a, b, c);
    DisplayResult("SignedMax1_A", a, b, c, smax1);
    DisplayResult("SignedMax2_A", a, b, c, smax2);
    std::cout << nl;

    a = -3; b = 28; c = 15;
    smax1 = SignedMax1_A(a, b, c);
    smax2 = SignedMax2_A(a, b, c);
    DisplayResult("SignedMax1_A", a, b, c, smax1);
    DisplayResult("SignedMax2_A", a, b, c, smax2);
    std::cout << nl;

    a = -25; b = -37; c = -17;
    smax1 = SignedMax1_A(a, b, c);
    smax2 = SignedMax2_A(a, b, c);
    DisplayResult("SignedMax1_A", a, b, c, smax1);
    DisplayResult("SignedMax2_A", a, b, c, smax2);
    std::cout << nl;
}
