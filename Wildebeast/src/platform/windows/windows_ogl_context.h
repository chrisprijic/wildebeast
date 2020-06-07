#pragma once

#include "platform/windows/windows_window.h"
#include "platform/opengl/ogl_context.h"

namespace wb {
    class WindowsOGLContext : public OGLContext {
        public:
            WindowsOGLContext(WindowsWindow* window);
            ~WindowsOGLContext();
            bool Init();
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

