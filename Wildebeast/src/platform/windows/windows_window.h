#pragma once

#include "wb/window.h"
#include <GLFW/glfw3.h>

namespace wb {
	class WindowsWindow : public Window {
		public:
			WindowsWindow(const WindowCtx& ctx);
			virtual ~WindowsWindow();
			
			void OnUpdate() override;

			unsigned int GetWidth() const override { return windowCtx.Width; }
			unsigned int GetHeight() const override { return windowCtx.Height; }

			void SetEventCallback(const EventCallbackFn& callback) override { windowCtx.EventCallback = callback; }
			void SetVSync(bool enabled) override;
			bool IsVSync() const override;

			virtual void* GetNativeWindow() const { return window; }
		private:
			virtual void Init(const WindowCtx& ctx);
			virtual void Shutdown();
		private:
			GLFWwindow* window;
			struct LocalWindowCtx {
				std::string Title;
				unsigned int Width, Height;
				bool VSync;

				EventCallbackFn EventCallback;
			};

			LocalWindowCtx windowCtx;
	};

}