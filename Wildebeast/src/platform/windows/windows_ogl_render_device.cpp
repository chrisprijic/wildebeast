#include "wbpch.h"
#include "platform/windows/windows_ogl_render_device.h"
#include "platform/windows/windows_ogl_device_context.h"

namespace wb {
    WindowsOGLRenderDevice::WindowsOGLRenderDevice(WindowsWindow* window) {
        this->window = window;
    }

    WindowsOGLRenderDevice::~WindowsOGLRenderDevice() {
        // TODO(Chris): clean up resources here
    }

    void WindowsOGLRenderDevice::Init() {
        // TODO(Chris): do we have any prep we need to do atm?
    }

    pvoid WindowsOGLRenderDevice::CreateSwapChain() {
        WB_CORE_ERROR("OGL TRYING TO CREATE SWAP CHAIN: not supported");
        return nullptr;
    }

    void WindowsOGLRenderDevice::Dispatch(pvoid cmdList) {
        WB_CORE_ERROR("OGL TRYING TO DISPATCH COMMAND LIST: not supported");
    }

    void WindowsOGLRenderDevice::SignalFence(pvoid fence, u64 fenceValue) {
        //TODO(Chris): support in future
    }

    pvoid WindowsOGLRenderDevice::CreateContext() {
        return new WindowsOGLDeviceContext(window);
    }

    void WindowsOGLRenderDevice::ResetContext(pvoid context) {
        WB_CORE_ERROR("OGL TRYING TO RESET CONTEXT: not supported");
    }

    pvoid WindowsOGLRenderDevice::getNativeDevice() {
        return nullptr;
    }

}