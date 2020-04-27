#include "wbpch.h"
#include "platform/opengl/opengl_graphics_context.h"

#ifdef WB_PLATFORM_WINDOWS
#include "platform/windows/windows_opengl_context.h"
#endif

namespace wb {
	GraphicsContext* OpenGLGraphicsContext::Create(Window* window) {
#ifdef WB_PLATFORM_WINDOWS
		return new WindowsOpenGLContext((WindowsWindow*)window);
#else
		WB_CORE_ERROR("Graphics Context for OpenGL only supports WB_PLATFORM_WINDOWS");
		return nullptr;
#endif
	}
}