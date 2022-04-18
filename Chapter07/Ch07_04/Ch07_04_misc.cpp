//------------------------------------------------
//               Ch07_04_misc.cpp
//------------------------------------------------

#include <iostream>
#include <random>
#include <cstring>
#include <string>
#include "Ch07_04.h"
#include "MT.h"
#include "AlignedMem.h"

bool CheckArgs(const uint8_t* pb_des, const uint8_t* pb_src, size_t num_pixels)
{
    if ((num_pixels == 0) || (num_pixels > c_NumPixelsMax))
        return false;
    if ((num_pixels & 0x3f) != 0)
        return false;
    if (!AlignedMem::IsAligned(pb_src, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(pb_des, c_Alignment))
        return false;
    return true;
}

void InitArray(uint8_t* x, size_t n, unsigned int rng_seed)
{
    MT::FillArray(x, n, 0, 255, rng_seed);
}

void DisplayResults(const uint8_t* pb_des1, const uint8_t* pb_des2,
    size_t num_pixels, CmpOp cmp_op, uint8_t cmp_val, size_t test_id)
{
    size_t num_non_zero = 0;
    bool are_same = memcmp(pb_des1, pb_des2, num_pixels * sizeof(uint8_t)) == 0;

    const std::string cmp_op_strings[] {"EQ", "NE", "LT", "LE", "GT", "GE"};

    if (are_same)
    {
        for (size_t i = 0; i < num_pixels; i++)
            num_non_zero += (pb_des1[i] != 0) ? 1 : 0;
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
