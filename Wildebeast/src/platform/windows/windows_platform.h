#pragma once

#include "wb/core/platform.h"
#include "wb/application/window.h"
#include "platform/windows/windows_window.h"


#include <Windows.h>

namespace wb{
    typedef struct WinEventParams {
        HWND hWnd;
        UINT uMsg;
        WPARAM wParam;
        LPARAM lParam;
    } WinEventParams;

    class WindowsPlatform : public Platform {
    public:
        WindowsPlatform();
        ~WindowsPlatform();

        void Init();
        void OnUpdate();

        Window* NewWindow(const WindowCtx& ctx = WindowCtx());

        LRESULT HandleWin32Message(WindowsWindow* window, WinEventParams params);
    private:
        static bool _wbGamepadConnected;
    };
}