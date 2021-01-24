#pragma once

#include "wb/graphics/render_device.h"
#include "wb/graphics/device_context.h"
#include "wb/graphics/swapchain.h"
#include "wb/graphics/types.h"

namespace wb {
    class Engine {
    public:
        static void CreateDeviceAndContext(IRenderDevice** ppRenderDevice, IDeviceContext** ppDeviceContext);
        // static void CreateSwapchain(SwapchainDesc& swapchainDesc, ISwapchain** ppSwapchain);
    };
}

