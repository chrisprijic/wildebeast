#include "wbpch.h"

#include "wb/application.h"

namespace wb {
	Application::Application()
	{
		window = Window::Create();
		window->SetEventCallback(std::bind(&Application::OnWindowClose, this));
		graphicsContext = GraphicsContext::Create(WB_GC_OPENGL, window);
		graphicsContext->Init();
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