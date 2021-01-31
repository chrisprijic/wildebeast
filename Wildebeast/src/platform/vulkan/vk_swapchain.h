#pragma once

#include "platform/vulkan/base.h"
#include "wb/core/types.h"
#include "wb/graphics/types.h"
#include "platform/vulkan/vk_render_device.h"
#include "platform/vulkan/vk_device_context.h"

namespace wb {
    class VkSwapchain {
    public:
        VkSwapchain(const SwapchainDesc& desc, VkRenderDevice* renderDevice, VkDeviceContext* deviceContext, void* window);

        SwapchainDesc desc;
        VkRenderDevice* renderDevice = nullptr;

        u32 desiredBufferCount = VK_NULL_HANDLE;
        SURFACE_TRANSFORM desiredPreTransform = SURFACE_TRANSFORM::IDENTITY;
        VkFormat colorFormat = VK_FORMAT_UNDEFINED;
        bool vsync = false;

        void* window = nullptr;
        VkSurfaceKHR surface = VK_NULL_HANDLE;
        VkSwapchainKHR swapchain = VK_NULL_HANDLE;
        std::vector<VkImageView> RTVs;
        std::vector<VkFramebuffer> RTVFBs;

        // synchronization
        std::vector<VkSemaphore> imageAcquiredSemaphores;
        std::vector<VkSemaphore> renderCompleteSemaphores;
        std::vector<VkFence> imageAcquiredFences;
        u32 currentBackBufferIndex = 0;
    private:
        void createSurface();
        void createVulkanSwapchain();
        void initBuffersAndViews();
        VkResult acquireNextImage(VkDeviceContext* deviceContext);
    };
}