#pragma once

#include "wb/window.h"

namespace wb {
	class WindowsWindow : public Window {
		public:
			WindowsWindow(const WindowCtx& ctx);
			virtual ~WindowsWindow();
			
			void OnUpdate() override;

			u32 GetWidth() const override { return windowCtx.Width; }
			u32 GetHeight() const override { return windowCtx.Height; }

			void SetEventCallback(const EventCallbackFn& callback) override { windowCtx.EventCallback = callback; }
			void SetVSync(bool enabled) override;
			bool IsVSync() const override;

			virtual pvoid GetNativeWindow() const { return window; }
		private:
			virtual void init(const WindowCtx& ctx);
			virtual void shutdown();

			virtual bool registerWindow();

			static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		private:
			HWND window;
			HDC hdc;
			HGLRC hrc;

			struct LocalWindowCtx {
				str Title;
				u32 Width, Height;
				bool VSync;

				EventCallbackFn EventCallback;
			};

			LocalWindowCtx windowCtx;

			static bool _wbWindowClassRegistered;
	};

}