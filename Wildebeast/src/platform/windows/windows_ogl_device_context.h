#pragma once

#include "platform/windows/windows_window.h"
#include "platform/opengl/ogl_device_context.h"

namespace wb {
    class WindowsOGLDeviceContext : public OGLDeviceContext {
        public:
            WindowsOGLDeviceContext(WindowsWindow* window);
            ~WindowsOGLDeviceContext();
            void Init();
            void SetVSync(bool enabled);
            void SwapBuffers();
            void MakeCurrent();
        private:
            HDC hdc;
            HGLRC hrc;
            HWND window;

            i32 glMaj;
            i32 glMin;
    };
}

