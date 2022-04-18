//------------------------------------------------
//               Ch03_05_misc.cpp
//------------------------------------------------

#include "Ch03_05.h"
#include "AlignedMem.h"
#include "MT.h"

bool CheckArgs(const double* x, size_t n)
{
    return ((n >= 2) && AlignedMem::IsAligned(x, c_Alignment));
}

void InitArray(double* x, size_t n)
{
   MT::FillArrayFP(x, n, c_ArrayFillMin, c_ArrayFillMax, c_RngSeed);
}

