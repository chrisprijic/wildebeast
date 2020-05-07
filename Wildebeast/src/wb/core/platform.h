#pragma once

#include "wb/core/core.h"
#include "wb/events/events.h"
#include "wb/application/window.h"

namespace wb {
    class Platform {
    public: 
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Platform() {}
        virtual void Init() = 0;
        virtual void OnUpdate() = 0;
        virtual void SetEventCallback(const EventCallbackFn& cb) { eventCallback = cb; }

        virtual Window* NewWindow(const WindowCtx& ctx = WindowCtx()) = 0;
        
        static Platform* Create();
    protected:
        EventCallbackFn eventCallback;
    };
}