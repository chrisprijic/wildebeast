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

#if !defined(WB_GRAPHICS_VULKAN) && !defined(WB_GRAPHICS_DX12) && !defined(WB_GRAPHICS_OPENGL)
#define WB_GRAPHICS_VULKAN
#endif

#include "wb/core/macros.h"
#include "wb/debug/debug.h"