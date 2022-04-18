//------------------------------------------------
//               Ch12_04.h
//------------------------------------------------

#pragma once

// Simple union for data exchange
union Uval
{
    int32_t m_I32;
    int64_t m_I64;
    float m_F32;
    double m_F64;
};

// The order of values in enum CvtOp must match the jump table
// that's defined in the .asm file.
enum class CvtOp : unsigned int
{
    I32_F32,       // int32_t to float
    F32_I32,       // float to int32_t
    I32_F64,       // int32_t to double
    F64_I32,       // double to int32_t
    I64_F32,       // int64_t to float
    F32_I64,       // float to int64_t
    I64_F64,       // int64_t to double
    F64_I64,       // double to int64_t
    F32_F64,       // float to double
    F64_F32,       // double to float
};

// Enumerated type for rounding control
enum class RC : unsigned int
{
    Nearest, Down, Up, Zero     // Do not change order
};

// Ch12_04_fasm.asm
extern "C" bool ConvertScalar_Aavx(Uval* a, Uval* b, CvtOp cvt_op, RC rc);
