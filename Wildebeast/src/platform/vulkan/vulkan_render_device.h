#pragma once

#include "platform/vulkan/base.h"
#include "wb/graphics/render_device.h"
#include "platform/windows/windows_window.h"

namespace wb {
    class VulkanRenderDevice : public RenderDevice {
	public:
		VulkanRenderDevice(Window* window);
		~VulkanRenderDevice();

		void Init() override;
		Swapchain* CreateSwapchain() override;
		virtual void Dispatch(pvoid cmdList) override;
		virtual pvoid CreateContext() override;
		virtual pvoid getNativeDevice() override;

		virtual pvoid getNativePhysicalDevice();
		virtual pvoid getNativeCommandQueue();
    private:
		WindowsWindow* window;

		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkPhysicalDevice physicalDevice;
		std::vector<const char*> physicalDeviceExtensions;
		u32 queueFamily = 0;
		VkDevice device;
		VkQueue queue;
		VkSurfaceKHR surface;
		VkCommandPool commandPool;
    };
}
