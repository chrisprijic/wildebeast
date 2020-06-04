#include "wbpch.h"
#include "platform/vulkan/vulkan_swapchain.h"

namespace wb {
    VulkanSwapchain::VulkanSwapchain(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, VkQueue queue) {
        this->physicalDevice = physicalDevice;
        this->device = device;
        this->surface = surface;
        this->queue = queue;

        VkFormat rtvFormat = VK_FORMAT_B8G8R8A8_SRGB;

        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        HRESULT result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfaceCapabilities);

        VkSwapchainCreateInfoKHR swapChainCreateInfo{};
        swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapChainCreateInfo.surface = surface;
        swapChainCreateInfo.minImageCount = 2;
        swapChainCreateInfo.imageFormat = rtvFormat;
        swapChainCreateInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        swapChainCreateInfo.imageExtent = VkExtent2D{ 1264, 681 };
        swapChainCreateInfo.imageArrayLayers = 1;
        swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapChainCreateInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
        swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapChainCreateInfo.clipped = VK_TRUE;
        swapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
        swapChainCreateInfo.preTransform = surfaceCapabilities.currentTransform;

        result = vkCreateSwapchainKHR(device, &swapChainCreateInfo, nullptr, &swapchain);

        vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);

        swapchainImages = new VkImage[imageCount];
        vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore);
        vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore);

        currentBufferIndex = 0;
    }

    VulkanSwapchain::~VulkanSwapchain() {
        delete[] swapchainImages;
    }

    pvoid VulkanSwapchain::GetBuffer(u32 buffer) {
        WB_ASSERT(buffer < imageCount, "trying to access buffer that doesn't exist (buffer < imageCount required)")(buffer, imageCount);
        return swapchainImages[buffer];
    }

    void VulkanSwapchain::acquireNextImage() {
        vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &currentBufferIndex);
    }

    u32 VulkanSwapchain::GetBackBufferIndex() {
        return currentBufferIndex;
    }

    u32 VulkanSwapchain::GetBackBufferCount() {
            return imageCount;
    }

    void VulkanSwapchain::Present(u32 vsync) {
        VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        VkSwapchainKHR swapChains[] = { swapchain };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &currentBufferIndex;
        presentInfo.pResults = nullptr; // Optional

        vkQueuePresentKHR(queue, &presentInfo);
    }

    pvoid VulkanSwapchain::getNativeSignalSemaphore() {
        return renderFinishedSemaphore;
    }

    pvoid VulkanSwapchain::getNativeWaitSemaphore() {
        return imageAvailableSemaphore;
    }
}