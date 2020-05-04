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

    typedef size_t size;
    typedef void* pvoid;
    typedef const void* cpvoid;

    typedef std::string str;

    static const bool FALSE = false;
    static const bool False = false;
    static const bool TRUE = true;
    static const bool True = true;
}