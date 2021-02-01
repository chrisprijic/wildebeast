#include "wbpch.h"

#include "vk_swapchain.h"
#include "platform/vulkan/vk_utils/vk_conversions.h"

namespace wb {
    VkSwapchain::VkSwapchain(const SwapchainDesc& desc, VkRenderDevice* renderDevice, VkDeviceContext* deviceContext, void* window)
        : renderDevice(renderDevice), deviceContext(deviceContext), window(window), desiredBufferCount(desc.BufferCount), desiredPreTransform(desc.PreTransform), desc(desc) {
        createSurface();
        createVulkanSwapchain();
        initBuffersAndViews();
        VK_CHECK_RESULT(acquireNextImage(deviceContext));
    }

    void VkSwapchain::createSurface() {
        if (surface != VK_NULL_HANDLE) {
            vkDestroySurfaceKHR(renderDevice->instance, surface, NULL);
        }

VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
#ifdef WB_PLATFORM_WINDOWS
surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
surfaceCreateInfo.hwnd = (HWND) window;
surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);
#endif
VK_CHECK_RESULT(vkCreateWin32SurfaceKHR(renderDevice->instance, &surfaceCreateInfo, nullptr, &surface));

VkBool32 presentSupport = VK_FALSE;
vkGetPhysicalDeviceSurfaceSupportKHR(renderDevice->physicalDevice, renderDevice->queueFamilyIndex, surface, &presentSupport);
if (!presentSupport) {
    WB_ERROR("Selected physical device does not support present capabilities for this window.");
}
    }

    void VkSwapchain::createVulkanSwapchain() {
        VkPhysicalDevice physicalDevice = renderDevice->physicalDevice;

        u32 formatCount = 0;
        VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, NULL));
        WB_ASSERT(formatCount > 0, "surface has 0 formats")(formatCount);

        std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
        VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, surfaceFormats.data()));
        WB_ASSERT(formatCount == surfaceFormats.size(), "surface formats provided don't match count provided")(formatCount, surfaceFormats.size());

        colorFormat = TexFormatToVkFormat(desc.ColorBufferFormat);
        VkColorSpaceKHR ColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
        if (formatCount == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
        {
            // If the format list includes just one entry of VK_FORMAT_UNDEFINED,
            // the surface has no preferred format.  Otherwise, at least one
            // supported format will be returned.

            // Do nothing
        } else {
            bool fmtFound = false;
            for (const auto& srfFmt : surfaceFormats)
            {
                if (srfFmt.format == colorFormat)
                {
                    fmtFound = true;
                    ColorSpace = srfFmt.colorSpace;
                    break;
                }
            }

            if (!fmtFound) {
                VkFormat replacementColorFormat = VK_FORMAT_UNDEFINED;
                switch (colorFormat)
                {
                    // clang-format off
                case VK_FORMAT_R8G8B8A8_UNORM: replacementColorFormat = VK_FORMAT_B8G8R8A8_UNORM; break;
                case VK_FORMAT_B8G8R8A8_UNORM: replacementColorFormat = VK_FORMAT_R8G8B8A8_UNORM; break;
                case VK_FORMAT_B8G8R8A8_SRGB:  replacementColorFormat = VK_FORMAT_R8G8B8A8_SRGB;  break;
                case VK_FORMAT_R8G8B8A8_SRGB:  replacementColorFormat = VK_FORMAT_B8G8R8A8_SRGB;  break;
                default: replacementColorFormat = VK_FORMAT_UNDEFINED;
                    // clang-format on
                }

                bool ReplacementFmtFound = false;
                for (const auto& SrfFmt : surfaceFormats)
                {
                    if (SrfFmt.format == replacementColorFormat)
                    {
                        ReplacementFmtFound = true;
                        ColorSpace = SrfFmt.colorSpace;
                        break;
                    }
                }

                if (ReplacementFmtFound)
                {
                    colorFormat = replacementColorFormat;
                    auto newColorBufferFormat = VkFormatToTexFormat(replacementColorFormat);
                    WB_CORE_INFO("Requested color buffer format is not supported by the surface and will be replaced with a simiar one");
                    desc.ColorBufferFormat = newColorBufferFormat;
                } else
                {
                    WB_CORE_WARN("Requested color buffer format is not supported by the surface");
                }
            }
        }

        VkSurfaceCapabilitiesKHR surfCapabilities = {};

        VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfCapabilities));

        uint32_t presentModeCount = 0;
        VK_CHECK_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, NULL));
        WB_ASSERT(presentModeCount > 0, "surface has no present modes")(presentModeCount);

        std::vector<VkPresentModeKHR> presentModes(presentModeCount);
        VK_CHECK_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes.data()));
        WB_ASSERT(presentModeCount == presentModes.size(), "surface modes provided do not match count provided")(presentModeCount, presentModes.size());

        VkSurfaceTransformFlagBitsKHR preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        if (desiredPreTransform != SURFACE_TRANSFORM::OPTIMAL) {
            preTransform = SurfaceTransformToVkSurfaceTransformFlag(desiredPreTransform);
            if ((surfCapabilities.supportedTransforms & preTransform) != 0) {
                desc.PreTransform = desiredPreTransform;
            } else {
                desiredPreTransform = SURFACE_TRANSFORM::OPTIMAL;
            }
        }

        if (desiredPreTransform == SURFACE_TRANSFORM::OPTIMAL) {
            preTransform = surfCapabilities.currentTransform;
            desc.PreTransform = VkSurfaceTransformFlagToSurfaceTransform(preTransform);
        }

        VkExtent2D extent{};
        // currentExtent is either both 0xFFFFFFFF or neither are 0xFFFFFFFF
        if (surfCapabilities.currentExtent.width == 0xFFFFFFFF && desc.Width != 0 && desc.Height != 0) {
            extent.width = std::min(std::max(desc.Width, surfCapabilities.minImageExtent.width), surfCapabilities.maxImageExtent.width);
            extent.height = std::min(std::max(desc.Height, surfCapabilities.minImageExtent.height), surfCapabilities.maxImageExtent.height);
        } else {
            extent = surfCapabilities.currentExtent;
        }

        extent.width = std::max(extent.width, 1u);
        extent.height = std::max(extent.height, 1u);
        desc.Width = extent.width;
        desc.Height = extent.height;

        VkPresentModeKHR swapPresentMode = vsync ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_MAILBOX_KHR;

        bool presentModeSupported = std::find(presentModes.begin(), presentModes.end(), swapPresentMode) != presentModes.end();
        if (!presentModeSupported) {
            WB_ASSERT(swapPresentMode != VK_PRESENT_MODE_FIFO_KHR, "invalid position to be in; FIFO mode is spec-guaranteed")(swapPresentMode);

            const char* presentModeName = nullptr;
#define PRESENT_MODE_CASE(Mode) \
    case Mode: presentModeName = #Mode; break;
            switch (swapPresentMode)
            {
                PRESENT_MODE_CASE(VK_PRESENT_MODE_IMMEDIATE_KHR)
                    PRESENT_MODE_CASE(VK_PRESENT_MODE_MAILBOX_KHR)
                    PRESENT_MODE_CASE(VK_PRESENT_MODE_FIFO_KHR)
                    PRESENT_MODE_CASE(VK_PRESENT_MODE_FIFO_RELAXED_KHR)
                    PRESENT_MODE_CASE(VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR)
                    PRESENT_MODE_CASE(VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR)
            default: presentModeName = "<UNKNOWN>";
            }
#undef PRESENT_MODE_CASE
            WB_CORE_WARN("Present mode is not supported. Defaulting to VK_PRESENT_MODE_FIFO_KHR.");

            swapPresentMode = VK_PRESENT_MODE_FIFO_KHR;
        }

        if (desiredBufferCount < surfCapabilities.minImageCount) {
            desiredBufferCount = surfCapabilities.minImageCount;
        }

        if (surfCapabilities.maxImageCount != 0 && desiredBufferCount > surfCapabilities.maxImageCount) {
            desiredBufferCount = surfCapabilities.maxImageCount;
        }

        u32 desiredNumberOfSwapChainImages = desiredBufferCount;

        VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[4] = {
            VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
            VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
            VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
            VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
        };

        for (uint32_t i = 0; i < _countof(compositeAlphaFlags); i++)
        {
            if (surfCapabilities.supportedCompositeAlpha & compositeAlphaFlags[i])
            {
                compositeAlpha = compositeAlphaFlags[i];
                break;
            }
        }

        auto oldSwapchain = swapchain;
        swapchain = VK_NULL_HANDLE;

        VkSwapchainCreateInfoKHR swapchain_ci{};

        swapchain_ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchain_ci.pNext = NULL;
        swapchain_ci.surface = surface;
        swapchain_ci.minImageCount = desiredNumberOfSwapChainImages;
        swapchain_ci.imageFormat = colorFormat;
        swapchain_ci.imageExtent.width = extent.width;
        swapchain_ci.imageExtent.height = extent.height;
        swapchain_ci.preTransform = preTransform;
        swapchain_ci.compositeAlpha = compositeAlpha;
        swapchain_ci.imageArrayLayers = 1;
        swapchain_ci.presentMode = swapPresentMode;
        swapchain_ci.oldSwapchain = oldSwapchain;
        swapchain_ci.clipped = VK_TRUE;
        swapchain_ci.imageColorSpace = ColorSpace;

        WB_ASSERT(u64(desc.Usage) != 0, "usage must be set")(u64(desc.Usage));

        if (desc.Usage & SWAP_CHAIN_USAGE_FLAGS::RENDER_TARGET)
            swapchain_ci.imageUsage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        if (desc.Usage & SWAP_CHAIN_USAGE_FLAGS::SHADER_INPUT)
            swapchain_ci.imageUsage |= VK_IMAGE_USAGE_SAMPLED_BIT;
        if (desc.Usage & SWAP_CHAIN_USAGE_FLAGS::COPY_SOURCE)
            swapchain_ci.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;

        swapchain_ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchain_ci.queueFamilyIndexCount = 0;
        swapchain_ci.pQueueFamilyIndices = NULL;

        VkDevice device = renderDevice->device;

        VK_CHECK_RESULT(vkCreateSwapchainKHR(device, &swapchain_ci, NULL, &swapchain));

        if (oldSwapchain != VK_NULL_HANDLE) {
            vkDestroySwapchainKHR(device, oldSwapchain, NULL);
            oldSwapchain = VK_NULL_HANDLE;
        }

        u32 swapchainImageCount = 0;

        VK_CHECK_RESULT(vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, NULL));
        WB_ASSERT(swapchainImageCount > 0, "swapchain image count is 0")(swapchainImageCount);

        if (swapchainImageCount != desc.BufferCount) {
            desc.BufferCount = swapchainImageCount;
        }

        imageAcquiredSemaphores.resize(swapchainImageCount);
        renderCompleteSemaphores.resize(swapchainImageCount);
        imageAcquiredFences.resize(swapchainImageCount);
        fencesInFlight.resize(swapchainImageCount, false);

        for (u32 i = 0; i < swapchainImageCount; ++i) {
            VkSemaphoreCreateInfo semaphore_ci{};

            semaphore_ci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
            semaphore_ci.pNext = NULL;
            semaphore_ci.flags = 0;

            VK_CHECK_RESULT(vkCreateSemaphore(device, &semaphore_ci, NULL, &imageAcquiredSemaphores[i]));
            VK_CHECK_RESULT(vkCreateSemaphore(device, &semaphore_ci, NULL, &renderCompleteSemaphores[i]));

            VkFenceCreateInfo fence_ci{};

            fence_ci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
            fence_ci.pNext = NULL;
            fence_ci.flags = 0;
            
            VK_CHECK_RESULT(vkCreateFence(device, &fence_ci, NULL, &imageAcquiredFences[i]));
        }
    }

    void VkSwapchain::initBuffersAndViews() {
        VkDevice device = renderDevice->device;

        RTVs.resize(desc.BufferCount);
        swapchainImagesInitialized.resize(desc.BufferCount, false);
        RTVFBs.resize(desc.BufferCount);

        u32 swapchainImageCount = desc.BufferCount;
        std::vector<VkImage> swapchainImages(swapchainImageCount);
        VK_CHECK_RESULT(vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, swapchainImages.data()));
        WB_ASSERT(swapchainImageCount == swapchainImages.size(), "swapchain images size doesn't equal provided number of swapchain images")(swapchainImageCount, swapchainImages.size());

        for (u32 i = 0; i < swapchainImageCount; ++i) {
            VkImageViewCreateInfo imageViewCreateInfo{};
            imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            imageViewCreateInfo.image = swapchainImages[i];
            imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            imageViewCreateInfo.format = TexFormatToVkFormat(desc.ColorBufferFormat);
            imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
            imageViewCreateInfo.subresourceRange.levelCount = 1;
            imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
            imageViewCreateInfo.subresourceRange.layerCount = 1;
            VK_CHECK_RESULT(vkCreateImageView(device, &imageViewCreateInfo, nullptr, &RTVs[i]));
        }
    }

    VkResult VkSwapchain::acquireNextImage(VkDeviceContext* deviceContext) {
        VkDevice device = renderDevice->device;
        u32 previousFrameIndex = currentBackBufferIndex;

        if (fencesInFlight[previousFrameIndex]) {
            VkFence previousFence = imageAcquiredFences[previousFrameIndex];
            if (vkGetFenceStatus(device, previousFence) == VK_NOT_READY) {
                VK_CHECK_RESULT(vkWaitForFences(device, 1, &previousFence, VK_TRUE, UINT64_MAX));
            }
            vkResetFences(device, 1, &previousFence);
            fencesInFlight[previousFrameIndex] = false;
        }

        VkFence currentFence = imageAcquiredFences[currentBackBufferIndex];
        VkSemaphore currentSemaphore = imageAcquiredSemaphores[currentBackBufferIndex];

        VkResult res = vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, currentSemaphore, currentFence, &currentBackBufferIndex);

        fencesInFlight[currentBackBufferIndex] = (res == VK_SUCCESS);

        if (res == VK_SUCCESS) {
            // TODO (Chris): need to wait for the semaphore within the buffer/context
            if (!swapchainImagesInitialized[currentBackBufferIndex]) {
                // TODO (Chris): set render targets
                // TODO (Chris): clear render target
                swapchainImagesInitialized[currentBackBufferIndex] = true;
            }
            // TODO (Chris): set render targets
        }

        return res;
    }

    void VkSwapchain::Present(u32 syncInterval) {
        if (syncInterval != 0 && syncInterval != 1) {
            WB_CORE_WARN("vulkan only supports 0 and 1 sync intervals");
        }

        // TODO (Chris): unbind back buffer from context

        if (!minimized) {
            // TODO (Chris): transition back buffer to present
            // TODO (Chris): add signal semaphore
        }

        // TODO (Chris): flush context

        if (!minimized) {
            VkPresentInfoKHR presentInfo = {};

            presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
            presentInfo.pNext = nullptr;
            presentInfo.waitSemaphoreCount = 1;
            // Unlike fences or events, the act of waiting for a semaphore also unsignals that semaphore (6.4.2)
            VkSemaphore waitSemaphore[] = { renderCompleteSemaphores[currentBackBufferIndex] };
            presentInfo.pWaitSemaphores = waitSemaphore;
            presentInfo.swapchainCount = 1;
            presentInfo.pSwapchains = &swapchain;
            presentInfo.pImageIndices = &currentBackBufferIndex;
            VkResult result = VK_SUCCESS;
            presentInfo.pResults = &result;

            renderDevice->QueuePresent(presentInfo);

            if (result == VK_SUBOPTIMAL_KHR || result == VK_ERROR_OUT_OF_DATE_KHR) {
                recreateVulkanSwapchain(deviceContext);
                currentBackBufferIndex = desc.BufferCount - 1; // so we start at 0 next image acquire
            } else {
                VK_CHECK_RESULT(result);
            }
        }

        if (desc.IsPrimary) {
            // TODO (Chris): finish frame, release stale resources
        }

        if (!minimized) {
            ++currentBackBufferIndex;
            if (currentBackBufferIndex >= desc.BufferCount)
                currentBackBufferIndex = 0;

            bool enableVSync = syncInterval != 0;

            VkResult err = (vsync == enableVSync ? acquireNextImage(deviceContext) : VK_ERROR_OUT_OF_DATE_KHR);
            if (err == VK_SUBOPTIMAL_KHR || err == VK_ERROR_OUT_OF_DATE_KHR) {
                vsync = enableVSync;
                recreateVulkanSwapchain(deviceContext);
                currentBackBufferIndex = desc.BufferCount - 1; // so we start at 0 next image acquire
                err = acquireNextImage(deviceContext);
            }
            VK_CHECK_RESULT(err);
        }
    }

    void VkSwapchain::waitForImageAcquiredFences() {
        VkDevice device = renderDevice->device;
        for (u32 i = 0; i < imageAcquiredFences.size(); ++i) {
            if (fencesInFlight[i]) {
                VkFence fence = imageAcquiredFences[i];
                if (vkGetFenceStatus(device, fence) == VK_NOT_READY) {
                    vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);
                }
            }
        }
    }

    void VkSwapchain::releaseSwapchainResources(VkDeviceContext* deviceContext, bool destroy) {
        if (swapchain == VK_NULL_HANDLE) {
            return;
        }

        if (deviceContext != nullptr) {
            // TODO (Chris): flush context

            // TODO (Chris): unbind back buffers from frame buffers
        }

        vkDeviceWaitIdle(renderDevice->device);

        waitForImageAcquiredFences();

        RTVs.clear();

        imageAcquiredSemaphores.clear();
        renderCompleteSemaphores.clear();
        imageAcquiredFences.clear();
        currentBackBufferIndex = 0;

        if (destroy) {
            vkDestroySwapchainKHR(renderDevice->device, swapchain, NULL);
            swapchain = VK_NULL_HANDLE;
        }
    }

    void VkSwapchain::recreateVulkanSwapchain(VkDeviceContext* deviceContext) {
        releaseSwapchainResources(deviceContext, false);

        {
            VkPhysicalDevice physicalDevice = renderDevice->physicalDevice;

            VkSurfaceCapabilitiesKHR surfCapabilities;

            VkResult res = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfCapabilities);
            if (res == VK_ERROR_SURFACE_LOST_KHR) {
                if (swapchain != VK_NULL_HANDLE) {
                    vkDestroySwapchainKHR(renderDevice->device, swapchain, NULL);
                    swapchain = VK_NULL_HANDLE;
                }

                createSurface();
            }

            createVulkanSwapchain();
            initBuffersAndViews();
        }
    }

    void VkSwapchain::Resize(u32 newWidth, u32 newHeight, SURFACE_TRANSFORM newPreTransform) {
        bool recreate = false;

        if (desc.Width != newWidth || desc.Height != newHeight || desc.PreTransform != newPreTransform) {
            recreate = true;
        }

        if (recreate) {
            if (deviceContext) {
                recreateVulkanSwapchain(deviceContext);
                VK_CHECK_RESULT(acquireNextImage(deviceContext));
            }
        }

        minimized = (newWidth == 0 && newHeight == 0);
    }
}