//------------------------------------------------
//               Ch17_03_misc.cpp
//------------------------------------------------

#include <iostream>
#include <random>
#include <cstring>
#include <string>
#include "Ch17_03.h"
#include "MT.h"
#include "AlignedMem.h"

bool CheckArgs(const uint8_t* des, const uint8_t* src, size_t num_pixels)
{
    // Make sure num_pixels is valid
    if (num_pixels == 0)
        return false;
    if ((num_pixels & 0x3f) != 0)
        return false;

    // Make sure src and des are properly aligned
    if (!AlignedMem::IsAligned(src, c_Alignment))
        return false;

    if (!AlignedMem::IsAligned(des, c_Alignment))
        return false;

    return true;
}

void InitArray(uint8_t* x, size_t n, unsigned int rng_seed)
{
    MT::FillArray(x, n, 0, 255, rng_seed);
}

void DisplayResults(const uint8_t* des1, const uint8_t* des2, size_t num_pixels, CmpOp cmp_op, uint8_t cmp_val, size_t test_id)
{
    size_t num_non_zero = 0;
    bool are_same = memcmp(des1, des2, num_pixels * sizeof(uint8_t)) == 0;

    const std::string cmp_op_strings[] {"EQ", "NE", "LT", "LE", "GT", "GE"};

    if (are_same)
    {
        for (size_t i = 0; i < num_pixels; i++)
            num_non_zero += (des1[i] != 0) ? 1 : 0;
    }

    std::cout << "\nTest #" << test_id << '\n';
    std::cout << "  num_pixels: " << num_pixels << '\n';
    std::cout << "  cmp_op:     " << cmp_op_strings[(int)cmp_op] << '\n';
    std::cout << "  cmp_val:    " << (int)cmp_val << '\n';

    if (are_same)
    {
        std::cout << "  Pixel masks are identical\n";
        std::cout << "  Number of non-zero mask pixels = " << num_non_zero << '\n';
    }
    else
        std::cout << "  Pixel masks are different\n";
}
