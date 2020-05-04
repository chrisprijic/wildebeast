#include "wbpch.h"
#include "platform/windows/windows_window.h"

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
					Event event;
					event.Type = WB_EVENT_QUIT;
					event.Quit = QuitEvent{};
					window->windowCtx.EventCallback(event);
				} break;
			}
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindow::shutdown() {
		DestroyWindow(window);
	}

	void WindowsWindow::OnUpdate() {
		MSG msg;

		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}