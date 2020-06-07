#include "wbpch.h"
#include "platform/windows/windows_ogl_context.h"

#include "GL/glew.h"
#include "GL/wglew.h"

namespace wb {
    WindowsOGLContext::WindowsOGLContext(WindowsWindow* win) {
        window = (HWND)win->GetNativeWindow();
        hdc = GetDC(window);
        hrc = NULL;
        glMaj = 0;
        glMin = 0;
    }

    WindowsOGLContext::~WindowsOGLContext() {
        ReleaseDC(window, hdc);
        wglDeleteContext(hrc);
    }

    bool WindowsOGLContext::Init() {
        PIXELFORMATDESCRIPTOR pfd;
        ZeroMemory(&pfd, sizeof(pfd));

        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;

        i32 pf = ChoosePixelFormat(hdc, &pfd);

        WB_ASSERT(pf, "Win32: Error defining pixel format for drawing context")(pf);
        if (!pf) {
            WB_CORE_ERROR("Win32: Error defining pixel format for drawing context");
            return false;
        }

        bool pixelFormatSet = SetPixelFormat(hdc, pf, &pfd);

        WB_ASSERT(pixelFormatSet, "Win32: Error setting desired pixel format")(pf, (void*)&pfd, GetLastError());
        if (!pixelFormatSet) {
            WB_CORE_ERROR("Win32: Error setting desired pixel format");
            return false;
        }

        DescribePixelFormat(hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

        HGLRC tempHRC = wglCreateContext(hdc);
        wglMakeCurrent(hdc, tempHRC);

        GLenum err = glewInit();
        if (GLEW_OK != err) {
            WB_CORE_ERROR("OpenGL: (GLEW) Failed to load OpenGL Context");
            return false;
        }

        if (wglewIsSupported("WGL_ARB_create_context") == 1) {
            std::pair<i32, i32> gl_versions[] = { {4, 6}, {4, 5}, {4, 4}, {4, 3}, {4, 2} };
            for (size i = 0; i < _countof(gl_versions) && hrc == NULL; i++) {
                const auto& version = gl_versions[i];
                glMaj = version.first;
                glMin = version.second;

                i32 attribs[] = {
                    WGL_CONTEXT_MAJOR_VERSION_ARB, glMaj,
                    WGL_CONTEXT_MINOR_VERSION_ARB, glMin,
                    WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                        GL_CONTEXT_PROFILE_MASK, GL_CONTEXT_CORE_PROFILE_BIT,
                        0, 0
                };

                hrc = wglCreateContextAttribsARB(hdc, 0, attribs);
            }
        }

        if (hrc == NULL) {
            WB_CORE_ERROR("Failed to initialize OpenGL context.");
            return false;
        }

        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(tempHRC);

        wglMakeCurrent(hdc, hrc);
        wglSwapIntervalEXT(0);

        // get GL info
        const GLubyte* glVersionString = glGetString(GL_VERSION);

        glGetIntegerv(GL_MAJOR_VERSION, &glMaj);
        glGetIntegerv(GL_MINOR_VERSION, &glMin);

        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* renderer = glGetString(GL_RENDERER);

        WB_CORE_INFO("Initialized OpenGL {0}.{1} on device {2} {3}", glMaj, glMin, vendor, renderer);

        return true;
    }

    void WindowsOGLContext::SetVSync(bool enabled) {
        if (wglSwapIntervalEXT != nullptr)
        {
            wglSwapIntervalEXT(enabled ? 1 : 0);
        }
    }

    void WindowsOGLContext::SwapBuffers() {
        ::SwapBuffers(hdc);
    }

    void WindowsOGLContext::MakeCurrent() {
        wglMakeCurrent(hdc, hrc);
    }
}