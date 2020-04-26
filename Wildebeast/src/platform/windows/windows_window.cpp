#include "wbpch.h"
#include "platform/windows/windows_window.h"

namespace wb {
	WindowsWindow::WindowsWindow() {
		int success = glfwInit();
		isOpen = 1;
		window = glfwCreateWindow(640, 480, "Application Window", nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSwapInterval(1);

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowsWindow* clazz = (WindowsWindow*)glfwGetWindowUserPointer(window);
			clazz->OnWindowClose();
		});
	}

	void WindowsWindow::OnUpdate() {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	int WindowsWindow::IsOpen() {
		return isOpen;
	}

	void WindowsWindow::OnWindowClose() {
		glfwDestroyWindow(window);
		glfwTerminate();
		isOpen = 0;
	}

	WindowsWindow::~WindowsWindow() {

	}
}