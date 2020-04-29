#include "wbpch.h"
#include "platform/windows/windows_ogl_device_context.h"

#include <glad/glad.h>

namespace wb {
	WindowsOGLDeviceContext::WindowsOGLDeviceContext(WindowsWindow* win) {
		window = (HWND)win->GetNativeWindow();
		hdc = GetDC(window);
	}

	WindowsOGLDeviceContext::~WindowsOGLDeviceContext() {
		ReleaseDC(window, hdc);
		wglDeleteContext(hrc);
	}

	void WindowsOGLDeviceContext::Init() {
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(pfd));

		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;

		i32 pf = ChoosePixelFormat(hdc, &pfd);
		if (!pf) {
			WB_CORE_ERROR("Win32: Error defining pixel format for drawing context");
			return;
		}

		if (!SetPixelFormat(hdc, pf, &pfd)) {
			WB_CORE_ERROR("Win32: Error setting desired pixel format");
			return;
		}

		DescribePixelFormat(hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		hrc = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hrc);

		i32 status = gladLoadGL();
		if (!status) {
			WB_CORE_ERROR("OpenGL: (Glad) Failed to load OpenGL Context");
		}
	}

	void WindowsOGLDeviceContext::SwapBuffers() {
		//TODO(Chris): move the clear color calls out into the Renderer API once we make it.
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		::SwapBuffers(hdc);
	}

	void WindowsOGLDeviceContext::MakeCurrent() {
		wglMakeCurrent(hdc, hrc);
	}
}