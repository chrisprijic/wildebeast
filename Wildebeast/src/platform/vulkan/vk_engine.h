#pragma once

#include "wb/graphics/engine.h"
#include "platform/vulkan/vk_render_device.h"
#include "platform/vulkan/vk_device_context.h"
#include "platform/vulkan/vk_swapchain.h"

namespace wb {
    class VkEngine {
    public:
        static void CreateDeviceAndContext(VkRenderDevice** ppRenderDevice, VkDeviceContext** ppDeviceContext);
        static void CreateSwapchain(SwapchainDesc& swapchainDesc, pvoid nativeWindow, VkRenderDevice* pRenderDevice, VkSwapchain** ppSwapchain);
    };
}

