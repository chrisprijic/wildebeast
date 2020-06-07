#include "wbpch.h"
#include "platform/opengl/ogl_context.h"

#ifdef WB_PLATFORM_WINDOWS
#include "platform/windows/windows_ogl_context.h"
#endif

namespace wb {
    OGLContext* OGLContext::Create(Window* window) {
#ifdef WB_PLATFORM_WINDOWS
        return new WindowsOGLContext((WindowsWindow*)window);
#else
        WB_CORE_ERROR("Graphics Context for OpenGL only supports WB_PLATFORM_WINDOWS");
        return nullptr;
#endif
    }
}