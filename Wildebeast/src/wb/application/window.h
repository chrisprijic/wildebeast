#pragma once

#include "wbpch.h"
#include "wb/core/core.h"

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
        virtual ~Window() {}

        virtual u32 GetWidth() const = 0;
        virtual u32 GetHeight() const = 0;
        virtual u32 GetDrawWidth() const = 0;
        virtual u32 GetDrawHeight() const = 0;

        // Window attributes
        virtual pvoid GetNativeWindow() const = 0;
    };

}