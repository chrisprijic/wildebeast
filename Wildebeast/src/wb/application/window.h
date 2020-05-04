#pragma once

#include "wbpch.h"
#include "wb/core/core.h"
#include "wb/events/events.h"

namespace wb {

	struct WindowCtx {
		str Title;
		u32 Width;
		u32 Height;

		WindowCtx(const str& title = "Wildebeast Engine",
			u32 width = 1280,
			u32 height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowCtx& props = WindowCtx());
	};

}