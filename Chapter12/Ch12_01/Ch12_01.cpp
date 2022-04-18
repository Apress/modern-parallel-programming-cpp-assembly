//------------------------------------------------
//               Ch12_01.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch12_01.h"

static void ConvertFtoC(void);
static void ConvertCtoF(void);

int main()
{
    ConvertFtoC();
    ConvertCtoF();
    return 0;
}

static void ConvertFtoC(void)
{
    const size_t w = 10;
    float deg_fvals[] = {-459.67f, -40.0f, 0.0f, 32.0f, 72.0f, 98.6f, 212.0f};
    size_t n = sizeof(deg_fvals) / sizeof(float);

    std::cout << "\n-------- ConvertFtoC Results --------\n";
    std::cout << std::fixed << std::setprecision(4);

    for (size_t i = 0; i < n; i++)
    {
        float deg_c = ConvertFtoC_Aavx(deg_fvals[i]);

        std::cout << "  i: " << i << "  ";
        std::cout << "f: " << std::setw(w) << deg_fvals[i] << "  ";
        std::cout << "c: " << std::setw(w) << deg_c << '\n';
    }
}

static void ConvertCtoF(void)
{
    const size_t w = 10;
    float deg_cvals[] = {-273.15f, -40.0f, -17.777778f, 0.0f, 25.0f, 37.0f, 100.0f};
    size_t n = sizeof(deg_cvals) / sizeof(float);

    std::cout << "\n-------- ConvertCtoF Results --------\n";
    std::cout << std::fixed << std::setprecision(4);

    for (size_t i = 0; i < n; i++)
    {
        float deg_f = ConvertCtoF_Aavx(deg_cvals[i]);

        std::cout << "  i: " << i << "  ";
        std::cout << "c: " << std::setw(w) << deg_cvals[i] << "  ";
        std::cout << "f: " << std::setw(w) << deg_f << '\n';
    }
}
