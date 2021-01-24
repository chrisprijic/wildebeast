#pragma once

#include "platform/vulkan/base.h"
#include "wb/core/types.h"

namespace wb {
    class VkRenderDevice {
    public:
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkInstance instance;
        std::vector<VkQueue> queues;
        u32 queueFamilyIndex = 0;
    };
}