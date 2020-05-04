#pragma once

#ifdef _WIN32
    /* Windows x64/x86 */
    #ifdef _WIN64
        /* Windows x64  */
    #define WB_PLATFORM_WINDOWS
    #else
        /* Windows x86 */
    #error "x86 Builds are not supported!"
    #endif
#else
    #error "Unsupported platform!"
#endif

#include "wb/core/macros.h"
#include "wb/debug/debug.h"