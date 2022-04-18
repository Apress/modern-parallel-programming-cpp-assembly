//------------------------------------------------
//               Ch03_04_misc.cpp
//------------------------------------------------

#include "Ch03_04.h"
#include "AlignedMem.h"
#include "MT.h"

bool CheckArgs(const float* x, size_t n)
{
    return ((n >= 2) && AlignedMem::IsAligned(x, c_Alignment));
}

void InitArray(float* x, size_t n)
{
   MT::FillArrayFP(x, n, c_ArrayFillMin, c_ArrayFillMax, c_RngSeed);
}
