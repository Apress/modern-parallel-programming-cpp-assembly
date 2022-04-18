//------------------------------------------------
//               Ch05_07.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Ch05_07.h"
#include "MatrixF64.h"
#include "AlignedMem.h"

static void MatrixVecMulF64(void);

int main()
{
    try
    {
        MatrixVecMulF64();
        MatrixVecMulF64_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch05_07 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void MatrixVecMulF64(void)
{
    const size_t num_vec = 10;
    MatrixF64 m(4, 4);
    AlignedArray<Vec4x1_F64> vec_a_aa(num_vec, c_Alignment);
    AlignedArray<Vec4x1_F64> vec_b1_aa(num_vec, c_Alignment);
    AlignedArray<Vec4x1_F64> vec_b2_aa(num_vec, c_Alignment);
    Vec4x1_F64* vec_a = vec_a_aa.Data();
    Vec4x1_F64* vec_b1 = vec_b1_aa.Data();
    Vec4x1_F64* vec_b2 = vec_b2_aa.Data();

    Init(m, vec_a, num_vec);
    MatVecMulF64_Cpp(vec_b1, m, vec_a, num_vec);
    MatVecMulF64_Iavx2(vec_b2, m, vec_a, num_vec);

    const unsigned int w = 8;
    std::cout << "Results for MatrixVecMulF64\n";
    std::cout << std::fixed << std::setprecision(1);

    for (size_t i = 0; i < num_vec; i++)
    {
        std::cout << "Test case #" << i << '\n';

        std::cout << "vec_b1: ";
        std::cout << "  " << std::setw(w) << vec_b1[i].W << ' ';
        std::cout << "  " << std::setw(w) << vec_b1[i].X << ' ';
        std::cout << "  " << std::setw(w) << vec_b1[i].Y << ' ';
        std::cout << "  " << std::setw(w) << vec_b1[i].Z << '\n';

        std::cout << "vec_b2: ";
        std::cout << "  " << std::setw(w) << vec_b2[i].W << ' ';
        std::cout << "  " << std::setw(w) << vec_b2[i].X << ' ';
        std::cout << "  " << std::setw(w) << vec_b2[i].Y << ' ';
        std::cout << "  " << std::setw(w) << vec_b2[i].Z << '\n';

        if (!VecCompare(&vec_b1[i], &vec_b2[i]))
            throw std::runtime_error("Error - vector compare failed");
    }
}
