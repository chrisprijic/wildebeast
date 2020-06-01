#pragma once

#include "wb/graphics/render_device.h"
#include "wb/application/window.h"

namespace wb {
    class OGLRenderDevice : public RenderDevice {
    public:
        void Init() = 0;
        pvoid CreateSwapChain() = 0;
        virtual void Dispatch(pvoid cmdList) = 0;
        virtual pvoid CreateContext() = 0;
        virtual pvoid getNativeDevice() = 0;

        static OGLRenderDevice* Create(Window* window);
    };
}
