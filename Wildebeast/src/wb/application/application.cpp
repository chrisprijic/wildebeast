#include "wbpch.h"

#include "wb/application/application.h"
#include "wb/events/event_router.h"

namespace wb {
    Application::Application() {
        window = Window::Create();
        window->SetEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        graphicsContext = DeviceContext::Create(WB_DEVICECONTEXT_OPENGL, window);
        graphicsContext->Init();
        graphicsContext->SetVSync(true);
    }


    Application::~Application() {}

    void Application::OnEvent(Event& e) {}

    void Application::onEvent(Event& e) {
        switch (e.Type) {
            case WB_EVENT_QUIT: {
                closeWindow();
            } break;
            default: {
                OnEvent(e);
            }
        }
    }

    void Application::closeWindow() {
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