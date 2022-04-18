//------------------------------------------------
//               Ch15_03_misc.cpp
//------------------------------------------------

#include "Ch15_03.h"
#include "AlignedMem.h"

bool CheckArgs(const ClipData* clip_data)
{
    if (clip_data->m_NumPixels == 0)
        return false;

    if (!AlignedMem::IsAligned(clip_data->m_PbSrc, c_Alignment))
        return false;

    if (!AlignedMem::IsAligned(clip_data->m_PbDes, c_Alignment))
        return false;

    return true;
}

