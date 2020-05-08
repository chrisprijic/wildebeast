#pragma once

#include "wb/core/platform.h"
#include "wb/application/window.h"

#ifndef _WB_WNDCLASSNAME
#define _WB_WNDCLASSNAME L"WB_0.0.1"
#endif

namespace wb {
    class WindowsWindow : public Window {
        public:
            WindowsWindow(Platform* platform, const WindowCtx& ctx);
            virtual ~WindowsWindow();
            
            u32 GetWidth() const override { return windowCtx.Width; }
            u32 GetHeight() const override { return windowCtx.Height; }

            virtual pvoid GetNativeWindow() const { return window; }
        private:
            virtual bool init(const WindowCtx& ctx);
            virtual void shutdown();

            bool registerWindow();

            static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

            static bool _wbWindowClassRegistered;
        private:
            Platform* platform;
            HWND window;
            HDC hdc;
            HGLRC hrc;
            bool isWindowCreated;

            struct LocalWindowCtx {
                str Title;
                u32 Width, Height;
                bool VSync;
            };

            LocalWindowCtx windowCtx;
    };

}