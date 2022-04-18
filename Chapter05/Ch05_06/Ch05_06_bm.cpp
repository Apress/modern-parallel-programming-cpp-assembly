//------------------------------------------------
//               Ch05_06_bm.cpp
//------------------------------------------------

#include <iostream>
#include "Ch05_06.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"

void MatrixVecMulF32_bm(void)
{
    std::cout << "\nRunning benchmark function MatrixVecMulF32_bm - please wait\n";

    const size_t num_vec = 1000000;

    MatrixF32 m(4, 4);
    AlignedArray<Vec4x1_F32> vec_a_aa(num_vec, c_Alignment);
    AlignedArray<Vec4x1_F32> vec_b1_aa(num_vec, c_Alignment);
    AlignedArray<Vec4x1_F32> vec_b2_aa(num_vec, c_Alignment);

    Vec4x1_F32* vec_a = vec_a_aa.Data();
    Vec4x1_F32* vec_b1 = vec_b1_aa.Data();
    Vec4x1_F32* vec_b2 = vec_b2_aa.Data();

    Init(m, vec_a, num_vec);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        MatVecMulF32_Cpp(vec_b1, m, vec_a, num_vec);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        MatVecMulF32_Iavx2(vec_b2, m, vec_a, num_vec);
        bmtt.Stop(i, 1);
    }

    std::string fn = bmtt.BuildCsvFilenameString("Ch05_06_MatrixVecMulF32_bm");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    std::cout << "Benchmark times save to file " << fn << '\n';
}
