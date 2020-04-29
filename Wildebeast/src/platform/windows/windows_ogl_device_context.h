#pragma once

#include "platform/windows/windows_window.h"
#include "platform/opengl/ogl_device_context.h"

namespace wb {
	class WindowsOGLDeviceContext : public OGLDeviceContext {
		public:
			WindowsOGLDeviceContext(WindowsWindow* window);
			~WindowsOGLDeviceContext();
			void Init();
			void SwapBuffers();
			void MakeCurrent();
		private:
			HDC hdc;
			HGLRC hrc;
			HWND window;
	};
}

