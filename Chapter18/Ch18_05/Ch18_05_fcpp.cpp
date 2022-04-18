//------------------------------------------------
//               Ch18_05_fcpp.cpp
//------------------------------------------------

#include <stdexcept>
#include <cstdint>
#include "Ch18_05.h"
#include "MatrixF32.h"
#include "AlignedMem.h"

// Permutation indices for matrix columns
alignas(64) const uint32_t c_MatIndCol0[] { 0, 4, 8, 12, 0, 4, 8, 12,
                                            0, 4, 8, 12, 0, 4, 8, 12 };
alignas(64) const uint32_t c_MatIndCol1[] { 1, 5, 9, 13, 1, 5, 9, 13,
                                            1, 5, 9, 13, 1, 5, 9, 13 };
alignas(64) const uint32_t c_MatIndCol2[] { 2, 6, 10, 14, 2, 6, 10, 14,
                                            2, 6, 10, 14, 2, 6, 10, 14 };
alignas(64) const uint32_t c_MatIndCol3[] { 3, 7, 11, 15, 3, 7, 11, 15,
                                            3, 7, 11, 15, 3, 7, 11, 15 };

// Permutation indices for vector components
alignas(64) const uint32_t c_VecIndW[] { 0, 0, 0, 0, 4, 4, 4, 4,
                                         8, 8, 8, 8, 12, 12, 12, 12 };
alignas(64) const uint32_t c_VecIndX[] { 1, 1, 1, 1, 5, 5, 5, 5,
                                         9, 9, 9, 9, 13, 13, 13, 13 };
alignas(64) const uint32_t c_VecIndY[] { 2, 2, 2, 2, 6, 6, 6, 6,
                                         10, 10, 10, 10, 14, 14, 14, 14 };
alignas(64) const uint32_t c_VecIndZ[] { 3, 3, 3, 3, 7, 7, 7, 7,
                                         11, 11, 11, 11, 15, 15, 15, 15 };

void MatVecMulF32_Cpp(Vec4x1_F32* vec_b, MatrixF32& m, Vec4x1_F32* vec_a, size_t num_vec)
{
    if (!CheckArgs(vec_b, m, vec_a, num_vec))
        throw std::runtime_error("MatVecMulF32_Cpp() - CheckArgs failed");

    const float* mm = m.Data();

    // Calculate matrix-vector products
    for (size_t i = 0; i < num_vec; i++)
    {
        vec_b[i].W =  mm[0] * vec_a[i].W + mm[1] * vec_a[i].X;
        vec_b[i].W += mm[2] * vec_a[i].Y + mm[3] * vec_a[i].Z;

        vec_b[i].X =  mm[4] * vec_a[i].W + mm[5] * vec_a[i].X;
        vec_b[i].X += mm[6] * vec_a[i].Y + mm[7] * vec_a[i].Z;

        vec_b[i].Y =  mm[8] * vec_a[i].W + mm[9] * vec_a[i].X;
        vec_b[i].Y += mm[10] * vec_a[i].Y + mm[11] * vec_a[i].Z;

        vec_b[i].Z =  mm[12] * vec_a[i].W + mm[13] * vec_a[i].X;
        vec_b[i].Z += mm[14] * vec_a[i].Y + mm[15] * vec_a[i].Z;
    }
}
