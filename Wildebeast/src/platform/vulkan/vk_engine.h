#pragma once

#include "wb/graphics/engine.h"
#include "platform/vulkan/vk_render_device.h"
#include "platform/vulkan/vk_device_context.h"

namespace wb {
    class VkEngine {
    public:
        static void CreateDeviceAndContext(VkRenderDevice** ppRenderDevice, VkDeviceContext** ppDeviceContext);
    };
}

