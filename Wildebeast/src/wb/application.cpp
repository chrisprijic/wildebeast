#include "wbpch.h"

#include "application.h"

#ifdef WB_PLATFORM_WINDOWS
	#include "platform/windows/windows_window.h"
#endif

namespace wb {
	Application::Application()
	{
#ifdef WB_PLATFORM_WINDOWS
		WindowsWindow* window = new WindowsWindow();
		while (window->IsOpen()) {
			window->OnUpdate();
		}
#endif
	}


	Application::~Application()
	{
	}

	void Application::run() {
		// while(true);
	}
}