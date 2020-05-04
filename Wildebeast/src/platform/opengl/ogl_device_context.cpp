#include "wbpch.h"
#include "platform/opengl/ogl_device_context.h"

#ifdef WB_PLATFORM_WINDOWS
#include "platform/windows/windows_ogl_device_context.h"
#endif

namespace wb {
    DeviceContext* OGLDeviceContext::Create(Window* window) {
#ifdef WB_PLATFORM_WINDOWS
        return new WindowsOGLDeviceContext((WindowsWindow*)window);
#else
        WB_CORE_ERROR("Graphics Context for OpenGL only supports WB_PLATFORM_WINDOWS");
        return nullptr;
#endif
    }
}