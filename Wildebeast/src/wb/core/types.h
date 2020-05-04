#pragma once

#include <cstdint>
#include <string>

namespace wb {
    typedef int64_t  i64;
    typedef int32_t  i32;
    typedef int16_t  i16;
    typedef int8_t   i8;

    typedef uint64_t u64;
    typedef uint32_t u32;
    typedef uint16_t u16;
    typedef uint8_t  u8;

    typedef float f32;
    typedef double f64;
    typedef f64 real;

    typedef u8 byte;
    typedef size_t size;
    typedef void* pvoid;
    typedef const void* cpvoid;
    typedef i64* pi64;
    typedef i32* pi32;
    typedef i16* pi16;
    typedef i8* pi8;
    typedef u64* pu64;
    typedef u32* pu32;
    typedef u16* pu16;
    typedef u8* pu8;
    typedef byte* pbyte;

    typedef std::string str;

    static const bool FALSE = false;
    static const bool False = false;
    static const bool TRUE = true;
    static const bool True = true;
}