#include "wbpch.h"
#include "platform/windows/windows_window.h"

#include <glad/glad.h>

namespace wb {
	bool WindowsWindow::_wbWindowClassRegistered = false;

	WCHAR* createWideStringFromUTF8(std::string str) {
		if(str.empty()) return L"";
		const char* source = str.c_str();
		WCHAR* target;

		int count = MultiByteToWideChar(CP_UTF8, 0, source, -1, NULL, 0);
		if (!count)
		{
			WB_CORE_ERROR("Win32: Failed to convert string from UTF-8");
			return NULL;
		}
		target = (WCHAR*)calloc(count, sizeof(WCHAR));

		if (!MultiByteToWideChar(CP_UTF8, 0, source, -1, target, count)) {
			WB_CORE_ERROR("Win32: Failed to convert string from UTF-8");

			free(target);
			return NULL;
		}

		return target;
	}

	WindowsWindow::WindowsWindow(const WindowCtx& ctx) {
		init(ctx);
	}

	WindowsWindow::~WindowsWindow() {
		shutdown();
	}

	void WindowsWindow::init(const WindowCtx& ctx) {
		windowCtx.Title = ctx.Title;
		windowCtx.Width = ctx.Width;
		windowCtx.Height = ctx.Height;

		if (registerWindow()) {

			window = CreateWindowExW(
				WS_EX_APPWINDOW,
				_WB_WNDCLASSNAME, 
				createWideStringFromUTF8(windowCtx.Title),
				WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				windowCtx.Width, 
				windowCtx.Height, 
				NULL, 
				NULL, 
				GetModuleHandleW(NULL), 
				NULL
			);

			if (!window) {
				WB_CORE_ERROR("Win32: Failed to instantiate window class [WINDOWS ERROR CODE: ({0})]", GetLastError());
				return;
			}

			// setup opengl
			hdc = GetDC(window);

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

			SetPropW(window, L"WB_WINDOW", this);

			ShowWindow(window, SW_SHOW);
		}
	}

	bool WindowsWindow::registerWindow() {
		if (_wbWindowClassRegistered) {
			return true;
		}

		_wbWindowClassRegistered = true;

		WNDCLASSEXW wc;

		ZeroMemory(&wc, sizeof(wc));
		
		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = (WNDPROC)WindowsWindow::windowProc;
		wc.hInstance = GetModuleHandleW(NULL);
		wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
		wc.lpszClassName = _WB_WNDCLASSNAME;

		if (!RegisterClassExW(&wc)) {
			WB_CORE_ERROR("Win32: Failed to register window class [WINDOWS ERROR CODE: ({0})]", GetLastError());
			return false;
		}

		return true;
	}

	LRESULT CALLBACK WindowsWindow::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		WindowsWindow* window = (WindowsWindow*)GetPropW(hWnd, L"WB_WINDOW");
		if (window) {
			switch (uMsg) {
				case WM_CLOSE: {
					window->windowCtx.EventCallback();
				} break;
			}
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindow::shutdown() {
		ReleaseDC(window, hdc);
		wglDeleteContext(hrc);
		DestroyWindow(window);
	}

	void WindowsWindow::OnUpdate() {
		MSG msg;

		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers(hdc);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		// TODO(Chris): enable once we have OpenGL
		windowCtx.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return windowCtx.VSync;
	}
}