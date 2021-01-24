#pragma once

#include "platform/vulkan/base.h"
#include "wb/core/types.h"
#include "wb/graphics/types.h"
#include "platform/vulkan/vk_render_device.h"

namespace wb {
    class VkSwapchain {
    public:
        SwapchainDesc* desc;
        VkRenderDevice* renderDevice;
        VkSurfaceKHR surface;
        VkSwapchainKHR swapchain;
        std::vector<VkImage> swapchainImages;
        std::vector<VkImageView> RTVs;
        std::vector<VkFramebuffer> RTVFBs;
        u32 currentBackBufferIndex = 0;
    };
}