#include "wbpch.h"

#include "wb/application.h"

namespace wb {
	Application::Application()
	{
		window = Window::Create();
		window->SetEventCallback(std::bind(&Application::OnWindowClose, this));
		graphicsContext = DeviceContext::Create(WB_DEVICECONTEXT_OPENGL, window);
		graphicsContext->Init();
		graphicsContext->SetVSync(true);
	}


	Application::~Application()
	{
	}

	void Application::OnWindowClose() {
		isRunning = false;
	}

	void Application::Run() {
		while (isRunning) {
			graphicsContext->MakeCurrent();
			window->OnUpdate();
			graphicsContext->SwapBuffers();
		}
	}
}