#pragma once

#include "wb/core/types.h"

namespace wb {
    typedef enum WINDOW_EVENT_TYPE {
        WB_WINDOWEVENT_SHOWN,
        WB_WINDOWEVENT_HIDDEN,
        WB_WINDOWEVENT_EXPOSED,
        WB_WINDOWEVENT_MOVED,
        WB_WINDOWEVENT_RESIZED,
        WB_WINDOWEVENT_MINIMIZED,
        WB_WINDOWEVENT_MAXIMIZED,
        WB_WINDOWEVENT_RESTORED,
        WB_WINDOWEVENT_ENTER,
        WB_WINDOWEVENT_LEAVE,
        WB_WINDOWEVENT_FOCUSED,
        WB_WINDOWEVENT_UNFOCUSED,
        WB_WINDOWEVENT_CLOSED
    } WINDOW_EVENT_TYPE;

    typedef struct WindowEvent {
        u32 Type;
        u32 Timestamp;
        u32 WindowID;
        u8  Event;
        i32 Width;
        i32 Height;
    } WindowEvent;

    typedef struct SysWinEvent {
        u32 Type;
        u32 Timestamp;
        u32 WindowID;
        // TODO(Chris): define the msg type for system-specific items.
    } SysWinEvent;
}