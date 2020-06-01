#pragma once

#include "platform/opengl/ogl_render_device.h"
#include "platform/windows/windows_window.h"

namespace wb {
    class WindowsOGLRenderDevice : public OGLRenderDevice {
    public:
        WindowsOGLRenderDevice(WindowsWindow* window);
        ~WindowsOGLRenderDevice();
        void Init() override;
        pvoid CreateSwapChain() override;
        virtual void Dispatch(pvoid cmdList) override;
        virtual pvoid CreateContext() override;
        virtual pvoid getNativeDevice() override;
    private:
        WindowsWindow* window;
    };
}
