//------------------------------------------------
//               Ch12_03.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "Ch12_03.h"

static void CompareF32(void);

int main()
{
    CompareF32();
    return 0;
}

static void CompareF32(void)
{
    const size_t n = 6;
    float a[n] {120.0, 250.0, 300.0, -18.0, -81.0, 42.0};
    float b[n] {130.0, 240.0, 300.0, 32.0, -100.0, 0.0};

    // Set NAN test value
    b[n - 1] = std::numeric_limits<float>::quiet_NaN();

    std::cout << "\n----- Results for CompareF32 -----\n";

    for (size_t i = 0; i < n; i++)
    {
        uint8_t cmp_results[c_NumCmpOps];

        CompareF32_Aavx(a[i], b[i], cmp_results);
        DisplayResults(a[i], b[i], cmp_results);
    }
}
