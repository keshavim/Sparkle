#pragma once

#include <cstdint>

#define BIT(x) 1 << x

// Signed integer types
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Unsigned integer types
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;


// Pointer-sized integers (optional, for portability)
typedef intptr_t  isize;
typedef uintptr_t usize;
