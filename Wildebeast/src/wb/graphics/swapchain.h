#pragma once

#include "wb/core/types.h"

namespace wb {
    class ISwapchain {
    public:
        virtual void Present(u32 vsync) = 0;
        virtual pvoid GetBuffer(u32 buffer) = 0; // will be returning an image/texture in the future
        virtual u32 GetBackBufferIndex() = 0;
        virtual u32 GetBackBufferCount() = 0;
    };
}