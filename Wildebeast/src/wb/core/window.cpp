#include "wbpch.h"
#include "wb/core/window.h"

#ifdef WB_PLATFORM_WINDOWS
    #include "platform/windows/windows_window.h"
#endif

namespace wb {

    Window* Window::Create(const WindowCtx& ctx)
    {
#ifdef WB_PLATFORM_WINDOWS
        return new WindowsWindow(ctx);
#else
        return nullptr;
#endif
    }

}