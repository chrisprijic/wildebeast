#include "wbpch.h"
#include "platform/windows/windows_opengl_context.h"

#include <glad/glad.h>

namespace wb {
	WindowsOpenGLContext::WindowsOpenGLContext(WindowsWindow* win) {
		window = (HWND)win->GetNativeWindow();
		hdc = GetDC(window);
	}

	WindowsOpenGLContext::~WindowsOpenGLContext() {
		ReleaseDC(window, hdc);
		wglDeleteContext(hrc);
	}

	void WindowsOpenGLContext::Init() {
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(pfd));

		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;

		int pf = ChoosePixelFormat(hdc, &pfd);
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

		int status = gladLoadGL();
		if (!status) {
			WB_CORE_ERROR("OpenGL: (Glad) Failed to load OpenGL Context");
		}
	}

	void WindowsOpenGLContext::SwapBuffers() {
		//TODO(Chris): move the clear color calls out into the Renderer API once we make it.
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		::SwapBuffers(hdc);
	}

	void WindowsOpenGLContext::MakeCurrent() {
		wglMakeCurrent(hdc, hrc);
	}
}