#include "wbpch.h"
#include "vk_engine.h"
#include "platform/vulkan/base.h"
#include "platform/vulkan/vk_utils/vk_debugger.h"

namespace wb {
    void VkEngine::CreateDeviceAndContext(VkRenderDevice** ppRenderDevice, VkDeviceContext** ppDeviceContext) {
        ////////////////////////////////////////////////////
        // VULKAN APPLICATION
        ////////////////////////////////////////////////////
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = nullptr;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Wildebeast";
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
        ////////////////////////////////////////////////////
        // VULKAN LAYERS AND EXTENSIONS
        ////////////////////////////////////////////////////
        u32 layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions2(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions2.data());

        ////////////////////////////////////////////////////
        // VULKAN INSTANCE
        ////////////////////////////////////////////////////
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        std::vector<char*> extensions = { "VK_KHR_surface" };
#ifdef WB_PLATFORM_WINDOWS
        extensions.push_back("VK_KHR_win32_surface");
#else
        WB_CORE_ERROR("unsupported platform attempting vulkan");
#endif
        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        createInfo.enabledExtensionCount = static_cast<u32>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<u32>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        VkInstance instance;
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        ////////////////////////////////////////////////////
        // VULKAN DEBUGGER
        ////////////////////////////////////////////////////
        if (enableValidationLayers) {
            utils::EnableDebugger(instance);
        }

        ////////////////////////////////////////////////////
        // VULKAN PHYSICAL DEVICES
        ////////////////////////////////////////////////////
        VkPhysicalDevice physicalDevice;
        std::vector<const char*> physicalDeviceExtensions;
        u32 queueFamily = 0;
        VkDevice device;

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
                } else {
                    WB_CORE_ERROR("physical device cannot be retrieved that has required swapchain support");
                }
            }
        }

        ////////////////////////////////////////////////////
        // VULKAN QUEUES
        ////////////////////////////////////////////////////
        u32 queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        for (u32 i = 0; i < queueFamilies.size(); i++) {
            VkBool32 presentSupport = false;
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
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

        ////////////////////////////////////////////////////
        // VULKAN DEVICE
        ////////////////////////////////////////////////////
        VkDeviceCreateInfo deviceCreateInfo{};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
        deviceCreateInfo.enabledExtensionCount = static_cast<u32>(physicalDeviceExtensions.size());
        deviceCreateInfo.ppEnabledExtensionNames = physicalDeviceExtensions.data();

        result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
        VkQueue queue;
        vkGetDeviceQueue(device, queueFamily, 0, &queue);
        std::vector<VkQueue> queues = std::vector<VkQueue>{ queue };

        *ppRenderDevice = new VkRenderDevice{
            physicalDevice,
            device,
            instance,
            queues,
            queueFamily,
        };

        *ppDeviceContext = new VkDeviceContext{
            *ppRenderDevice,
            false,
        };
    }

    void VkEngine::CreateSwapchain(SwapchainDesc& swapchainDesc, pvoid nativeWindow, VkRenderDevice* pRenderDevice, VkDeviceContext* pDeviceContext, VkSwapchain** ppSwapchain) {
        *ppSwapchain = new VkSwapchain(swapchainDesc, pRenderDevice, pDeviceContext, nativeWindow);
    }
}