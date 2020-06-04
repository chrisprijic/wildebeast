#pragma once

#include "wb/graphics/swapchain.h"
#include "platform/vulkan/base.h"

namespace wb {
    class VulkanSwapchain : public Swapchain {
    public:
        VulkanSwapchain(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, VkQueue queue);
        ~VulkanSwapchain();

        virtual pvoid GetBuffer(u32 buffer) override; // will be returning an image/texture in the future
        virtual u32 GetBackBufferIndex() override;
        virtual void Present(u32 vsync) override;
        virtual u32 GetBackBufferCount() override;

        pvoid getNativeSwapchain() { return swapchain; }
        pvoid getNativeSignalSemaphore();
        pvoid getNativeWaitSemaphore();
    private:
        void acquireNextImage();

        u32 currentBufferIndex;
        u32 imageCount;
        VkImage* swapchainImages;
        VkSwapchainKHR swapchain;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkSurfaceKHR surface;
        VkQueue queue;
        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
    };
}
