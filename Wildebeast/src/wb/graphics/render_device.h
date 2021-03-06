#pragma once

#include "wb/core/types.h"
#include "wb/application/window.h"
#include "wb/graphics/swapchain.h"

namespace wb {
    enum RENDERDEVICE_TYPE {
        WB_RENDERDEVICE_NONE = 0,
        WB_RENDERDEVICE_OPENGL,
        WB_RENDERDEVICE_DIRECTX,
        WB_RENDERDEVICE_VULKAN,

    };

    class RenderDevice {
    public:
        virtual void Init() = 0;
        virtual Swapchain* CreateSwapchain() = 0;
        virtual void Dispatch(pvoid cmdList) = 0;
        virtual pvoid CreateContext() = 0;
        virtual pvoid getNativeDevice() = 0;
    
        static RenderDevice* Create(RENDERDEVICE_TYPE type, Window* window);
    };
}