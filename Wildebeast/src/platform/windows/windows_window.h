#pragma once

#include <GLFW/glfw3.h>

namespace wb {
	class WindowsWindow {
		public:
			WindowsWindow();
			virtual ~WindowsWindow();
			void OnUpdate();
			int IsOpen();
			void OnWindowClose();
		private:
			GLFWwindow* window;
			int isOpen;
	};

}