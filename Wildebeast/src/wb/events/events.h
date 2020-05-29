#pragma once

#include "wb/events/input_events.h"
#include "wb/events/window_events.h"
#include "wb/input/mouse.h"
#include "wb/input/keyboard.h"
#include "wb/input/gamepad.h"

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
        WB_EVENT_TEXT_INPUT,

        // mouse events
        WB_EVENT_MOUSE_MOVED			= 0x400,
        WB_EVENT_MOUSE_PRESSED,
        WB_EVENT_MOUSE_RELEASED,
        WB_EVENT_MOUSE_SCROLLED,

        // gamepad
        WB_EVENT_GAMEPAD_CONNECTED      = 0x500,
        WB_EVENT_GAMEPAD_DISCONNECTED,
        WB_EVENT_GAMEPAD_STATE,

        WB_EVENT_TOTAL_TYPES	= 0xFFFF
    } EVENT_TYPE;

    inline std::ostream& operator<<(std::ostream& os, EVENT_TYPE mousecode) {
        os << static_cast<int32_t>(mousecode);
        return os;
    }

    typedef struct GenericEvent {
        u32 Type;
        u32 Timestamp;
    } GenericEvent;

    typedef struct QuitEvent {

    } QuitEvent;

    // current size: 25 bytes (28 bytes when padded)
    typedef union event {
        u32 Type;

        GenericEvent		Generic;
        QuitEvent			Quit;
        WindowEvent         Window;
        SysWinEvent         SysWin;
        KeyboardEvent		Key;
        TextEvent           Text;
        MouseMoveEvent		Motion;
        MouseButtonEvent	Button;
        MouseScrollEvent	Scroll;
        GamepadEvent        Gamepad;

        // padding to wrap size to largest alignment 
        // (4 bytes): 25 -> 28
        u8 padding[28];
    } Event;

}