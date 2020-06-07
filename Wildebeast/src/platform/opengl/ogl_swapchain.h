#pragma once

#include "wb/graphics/swapchain.h"
#include "platform/opengl/ogl_context.h"

namespace wb {
    class OGLSwapchain : public Swapchain {
    public:
        OGLSwapchain(OGLContext* dc) { oglContext = dc; backBufferIndex = 0; };
        ~OGLSwapchain() {};
        virtual void Present(u32 vsync) override { oglContext->SwapBuffers(); backBufferIndex = (backBufferIndex++) % 2; };
        virtual pvoid GetBuffer(u32 buffer) override { return nullptr; };
        virtual u32 GetBackBufferIndex() { return backBufferIndex; };
        virtual u32 GetBackBufferCount() { return 2; }
    private:
        u32 backBufferIndex;
        OGLContext* oglContext;
    };
}