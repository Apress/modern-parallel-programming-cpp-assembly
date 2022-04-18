//------------------------------------------------
//               Ch16_04.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Ch16_04.h"
#include "MatrixF32.h"
#include "AlignedMem.h"

static void MatrixVecMulF32(void);

int main()
{
    try
    {
        MatrixVecMulF32();
        MatrixVecMulF32_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch16_04 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void MatrixVecMulF32(void)
{
    const char nl = '\n';
    const size_t num_vec = 10;

    MatrixF32 m(4, 4);
    AlignedArray<Vec4x1_F32> vec_a_aa(num_vec, c_Alignment);
    AlignedArray<Vec4x1_F32> vec_b1_aa(num_vec, c_Alignment);
    AlignedArray<Vec4x1_F32> vec_b2_aa(num_vec, c_Alignment);

    Vec4x1_F32* vec_a = vec_a_aa.Data();
    Vec4x1_F32* vec_b1 = vec_b1_aa.Data();
    Vec4x1_F32* vec_b2 = vec_b2_aa.Data();

    Init(m, vec_a, num_vec);

    MatVecMulF32_Cpp(vec_b1, m, vec_a, num_vec);
    MatVecMulF32_Aavx2(vec_b2, m.Data(), vec_a, num_vec);

    std::cout << "Results for MatrixVecMulF32\n";

    const unsigned int w = 8;
    std::cout << std::fixed << std::setprecision(1);

    for (size_t i = 0; i < num_vec; i++)
    {
        std::cout << "Test case #" << i << nl;

        std::cout << "vec_b1: ";
        std::cout << "  " << std::setw(w) << vec_b1[i].W << ' ';
        std::cout << "  " << std::setw(w) << vec_b1[i].X << ' ';
        std::cout << "  " << std::setw(w) << vec_b1[i].Y << ' ';
        std::cout << "  " << std::setw(w) << vec_b1[i].Z << nl;

        std::cout << "vec_b2: ";
        std::cout << "  " << std::setw(w) << vec_b2[i].W << ' ';
        std::cout << "  " << std::setw(w) << vec_b2[i].X << ' ';
        std::cout << "  " << std::setw(w) << vec_b2[i].Y << ' ';
        std::cout << "  " << std::setw(w) << vec_b2[i].Z << nl;

        if (!VecCompare(&vec_b1[i], &vec_b2[i]))
            throw std::runtime_error("Error - vector compare failed (b1/b2)");
    }
}
