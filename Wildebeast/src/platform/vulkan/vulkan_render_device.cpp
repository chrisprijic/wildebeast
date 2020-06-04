#include "wbpch.h"
#include "platform/vulkan/vulkan_render_device.h"
#include "platform/vulkan/vulkan_swapchain.h"

namespace wb {

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {

        //std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    VulkanRenderDevice::VulkanRenderDevice(Window* window) {
        this->window = (WindowsWindow*)window;
    }

    VulkanRenderDevice::~VulkanRenderDevice() {
        // TODO(Chris): cleanup here
    }

    void VulkanRenderDevice::Init() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

#ifdef WB_DEBUG
        const bool enableValidationLayers = true;
#else
        const bool enableValidationLayers = false;
#endif

        u32 layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions2(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions2.data());

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        std::vector<char*> extensions = { "VK_KHR_surface", "VK_KHR_win32_surface" };
        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        createInfo.enabledExtensionCount = static_cast<u32>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT createDebugInfo{};
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<u32>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            createDebugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            createDebugInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            createDebugInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            createDebugInfo.pfnUserCallback = debugCallback;
            createDebugInfo.pUserData = nullptr; // Optional

            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &createDebugInfo;

        } else {
            createInfo.enabledLayerCount = 0;
        }

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        CreateDebugUtilsMessengerEXT(instance, &createDebugInfo, nullptr, &debugMessenger);

        VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        surfaceCreateInfo.hwnd = (HWND) window->GetNativeWindow();
        surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

        result = vkCreateWin32SurfaceKHR(instance, &surfaceCreateInfo, nullptr, &surface);

        u32 deviceCount = 0;
        result = vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
        result = vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());
        // for now, find discrete GPU rather than integrated graphics
        for (VkPhysicalDevice physdev : physicalDevices) {
            VkPhysicalDeviceProperties deviceProperties;
            VkPhysicalDeviceFeatures deviceFeatures;
            vkGetPhysicalDeviceProperties(physdev, &deviceProperties);
            vkGetPhysicalDeviceFeatures(physdev, &deviceFeatures);

            u32 extensionCount;
            result = vkEnumerateDeviceExtensionProperties(physdev, nullptr, &extensionCount, nullptr);
            std::vector<VkExtensionProperties> availableExtensions(extensionCount);
            result = vkEnumerateDeviceExtensionProperties(physdev, nullptr, &extensionCount, availableExtensions.data());

            if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                bool found = false;

                for (VkExtensionProperties prop : availableExtensions) {
                    if (strcmp(prop.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    physicalDeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
                    physicalDevice = physdev;
                    break;
                }
            }
        }

        u32 queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        for (u32 i = 0; i < queueFamilies.size(); i++) {
            VkBool32 presentSupport = false;
            result = vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && presentSupport) {
                queueFamily = i;
                break;
            }
        }

        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo deviceCreateInfo{};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
        deviceCreateInfo.enabledExtensionCount = static_cast<u32>(physicalDeviceExtensions.size());
        deviceCreateInfo.ppEnabledExtensionNames = physicalDeviceExtensions.data();

        result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
        vkGetDeviceQueue(device, queueFamily, 0, &queue);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamily;
        poolInfo.flags = 0; // Optional

        vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
    }

    Swapchain* VulkanRenderDevice::CreateSwapchain() {
        return new VulkanSwapchain(physicalDevice, device, surface, queue);
    }

    void VulkanRenderDevice::Dispatch(pvoid cmdList) {
        vkQueueSubmit(queue, 1, (VkSubmitInfo*)cmdList, VK_NULL_HANDLE);
    }

    pvoid VulkanRenderDevice::CreateContext() {
        VkCommandBuffer commandBuffer;

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;

        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

        return commandBuffer;
    }

    pvoid VulkanRenderDevice::getNativeDevice() {
        return device;
    }

    pvoid VulkanRenderDevice::getNativePhysicalDevice() {
        return physicalDevice;
    }

    pvoid VulkanRenderDevice::getNativeCommandQueue() {
        return queue;
    }
}