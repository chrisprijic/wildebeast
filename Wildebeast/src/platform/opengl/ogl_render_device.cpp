#include "wbpch.h"
#include "platform/opengl/ogl_render_device.h"

#ifdef WB_PLATFORM_WINDOWS
#include "platform/windows/windows_ogl_render_device.h"
#endif

namespace wb {
    OGLRenderDevice* OGLRenderDevice::Create(Window* window) {
#ifdef WB_PLATFORM_WINDOWS
        return new WindowsOGLRenderDevice((WindowsWindow*) window);
#else
        WB_CORE_ERROR("Graphics Context for OpenGL only supports WB_PLATFORM_WINDOWS");
        return nullptr;
#endif
    }
}