#include "wbpch.h"

#include "application.h"
#include <GLFW/glfw3.h>

namespace wb {
	Application::Application()
	{
		window = Window::Create();
		window->SetEventCallback(std::bind(&Application::OnWindowClose, this));
	}


	Application::~Application()
	{
	}

	void Application::OnWindowClose() {
		isRunning = false;
	}

	void Application::Run() {
		while (isRunning) {
			float time = (float)glfwGetTime();
			window->OnUpdate();
		}
	}
}