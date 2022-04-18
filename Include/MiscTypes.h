//------------------------------------------------
//               MiscTypes.h
//------------------------------------------------

#pragma once
#include <cstdint>

#if defined(_M_AMD64) || defined(__x86_64__)
typedef int64_t indx_t;
#elif defined(_M_IX86) || defined(__i386__)
typedef int32_t indx_t;
#else
#error "typedef indx_t is undefined"
#endif
