#include "wbpch.h"
#include "graphics_context.h"
#include "platform/opengl/opengl_graphics_context.h"

namespace wb {
	GraphicsContext* GraphicsContext::Create(GRAPHICS_CONTEXT_TYPE type, Window* window) {
		switch (type) {
			case WB_GC_OPENGL: {
				return OpenGLGraphicsContext::Create(window);
			} break;
			default:
				WB_CORE_ERROR("Graphics Context is not supported!");
		}
		return nullptr;
	}
}