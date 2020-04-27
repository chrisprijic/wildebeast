#pragma once

#include "platform/windows/windows_window.h"
#include "platform/opengl/opengl_graphics_context.h"

namespace wb {
	class WindowsOpenGLContext : public OpenGLGraphicsContext {
		public:
			WindowsOpenGLContext(WindowsWindow* window);
			~WindowsOpenGLContext();
			void Init();
			void SwapBuffers();
			void MakeCurrent();
		private:
			HDC hdc;
			HGLRC hrc;
			HWND window;
	};
}

