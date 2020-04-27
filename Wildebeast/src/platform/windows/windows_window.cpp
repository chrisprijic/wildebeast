#include "wbpch.h"
#include "platform/windows/windows_window.h"

namespace wb {
	static void GLFWErrorCallback(int error, const char* description)
	{
		WB_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowCtx& ctx) {
		Init(ctx);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowCtx& ctx) {
		windowCtx.Title = ctx.Title;
		windowCtx.Width = ctx.Width;
		windowCtx.Height = ctx.Height;

		int success = glfwInit();
		glfwSetErrorCallback(GLFWErrorCallback);

		window = glfwCreateWindow((int)windowCtx.Width, (int)windowCtx.Height, windowCtx.Title.c_str(), nullptr, nullptr);

		glfwSetWindowUserPointer(window, &windowCtx);
		SetVSync(true);

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			LocalWindowCtx& ctx = *(LocalWindowCtx*)glfwGetWindowUserPointer(window);
			ctx.EventCallback();
		});
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		// TODO(Chris): enable once we have OpenGL
		/*if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}*/

		windowCtx.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return windowCtx.VSync;
	}
}