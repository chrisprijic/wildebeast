#pragma once

#include "platform/vulkan/base.h"
#include "platform/vulkan/vk_render_device.h"

namespace wb {
    class VkDeviceContext {
    public:
        VkRenderDevice* renderDevice;
        bool isDeferred;
    };
}