#include "wbpch.h"
#include "platform/windows/windows_ogl_render_device.h"
#include "platform/opengl/ogl_swapchain.h"

namespace wb {
    WindowsOGLRenderDevice::WindowsOGLRenderDevice(WindowsWindow* window) {
        this->window = window;
        this->oglContext = new WindowsOGLContext(window);
    }

    WindowsOGLRenderDevice::~WindowsOGLRenderDevice() {
        // TODO(Chris): clean up resources here
    }

    void WindowsOGLRenderDevice::Init() {
        // TODO(Chris): do we have any prep we need to do atm?
    }

    Swapchain* WindowsOGLRenderDevice::CreateSwapchain() {
        return new OGLSwapchain(oglContext);
    }

    void WindowsOGLRenderDevice::Dispatch(pvoid cmdList) {
        WB_CORE_ERROR("OGL TRYING TO DISPATCH COMMAND LIST: not supported");
    }

    pvoid WindowsOGLRenderDevice::CreateContext() {
        return this->oglContext;
    }

    pvoid WindowsOGLRenderDevice::getNativeDevice() {
        return nullptr;
    }
}