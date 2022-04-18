//------------------------------------------------
//               Ch07_04.h
//------------------------------------------------

#pragma once
#include <cstddef>
#include <cstdint>

// Compare operators
enum class CmpOp { EQ, NE, LT, LE, GT, GE };

// Ch07_04_fcpp.cpp
extern void ComparePixels_Cpp(uint8_t* pb_des, const uint8_t* pb_src,
    size_t num_pixels, CmpOp cmp_op, uint8_t cmp_val);
extern void ComparePixels_Iavx512(uint8_t* pb_des, const uint8_t* pb_src,
    size_t num_pixels, CmpOp cmp_op, uint8_t cmp_val);

// Ch07_04_misc.cpp
extern bool CheckArgs(const uint8_t* pb_des, const uint8_t* pb_src,
    size_t num_pixels);
extern void DisplayResults(const uint8_t* pb_des1, const uint8_t* pb_des2,
    size_t num_pixels, CmpOp cmp_op, uint8_t cmp_val, size_t test_id);
extern void InitArray(uint8_t* x, size_t n, unsigned int seed);

// Miscellaneous constants
const size_t c_Alignment = 64;
const size_t c_NumPixelsMax = 16 * 1024 * 1024;
