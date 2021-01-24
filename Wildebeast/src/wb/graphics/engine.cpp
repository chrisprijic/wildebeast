#include "wbpch.h"
#include "engine.h"

namespace wb {
    static void CreateDeviceAndContext(IRenderDevice** ppRenderDevice, IDeviceContext** ppDeviceContext) {
#ifdef WB_GRAPHICS_VULKAN
        //return VkEngine.CreateDeviceAndContext(ppRenderDevice, ppDeviceContext);
#else
    WB_CORE_ERROR("graphics type not supported.")
#endif
    }
}