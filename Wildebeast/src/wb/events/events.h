#pragma once

#include "wb/events/input_events.h"

namespace wb {

    typedef enum EVENT_TYPE {
        // unused
        WB_EVENT_NONE					= 0,

        // application events
        WB_EVENT_QUIT					= 0x100,

        // window events
        WB_EVENT_WINDOW_EVENT			= 0x200,
        WB_EVENT_SYSWIN_EVENT,
        
        // keyboard events
        WB_EVENT_KEY_PRESSED			= 0x300,
        WB_EVENT_KEY_REPEAT,
        WB_EVENT_KEY_RELEASED,

        // mouse events
        WB_EVENT_MOUSE_MOVED			= 0x400,
        WB_EVENT_MOUSE_PRESSED,
        WB_EVENT_MOUSE_RELEASED,
        WB_EVENT_MOUSE_SCROLLED,

        WB_EVENT_TOTAL_TYPES	= 0xFFFF
    } EVENT_TYPE;

    typedef struct GenericEvent {
        u32 Type;
        u32 Timestamp;
    } GenericEvent;

    typedef struct QuitEvent {

    } QuitEvent;

    // current size: 21 bytes (24 bytes when padded)
    typedef union event {
        u32 Type;

        GenericEvent		Generic;
        QuitEvent			Quit;
        KeyboardEvent		Key;
        MouseMoveEvent		Motion;
        MouseButtonEvent	Button;
        MouseScrollEvent	Scroll;

        // padding to wrap size to largest alignment 
        // (4 bytes): 21 -> 24
        u8 padding[24];
    } Event;

}