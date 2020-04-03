#pragma once

#include <cstdint>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef unsigned char byte;

typedef unsigned char* AnsiString;
typedef void* VoidPtr;

#ifdef GE_DOUBLE_PRECISION
typedef double real;
#else
typedef float real;
#endif
