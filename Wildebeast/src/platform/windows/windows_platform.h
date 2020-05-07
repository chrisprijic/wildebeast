#pragma once

#include "wb/core/platform.h"
#include "wb/application/window.h"


#include <Windows.h>

namespace wb{
    class WindowsPlatform : public Platform {
    public:
        WindowsPlatform();
        ~WindowsPlatform();

        void Init();
        void OnUpdate();

        Window* NewWindow(const WindowCtx& ctx = WindowCtx());

        LRESULT windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    private:
        static bool _wbGamepadConnected;
    };
}