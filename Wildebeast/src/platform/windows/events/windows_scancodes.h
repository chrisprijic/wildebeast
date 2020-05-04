#pragma once

#include "wb/core/types.h"
#include "wb/events/events.h"

namespace wb {
    static const u32 windows_scancode_table[] = {
        //	0						1						2						3							4					5						6						7 
        //	8						9						A						B							C					D						E						F 
            WB_KEYCODE_UNKNOWN,		WB_KEYCODE_ESCAPE,		WB_KEYCODE_1,			WB_KEYCODE_2,				WB_KEYCODE_3,		WB_KEYCODE_4,			WB_KEYCODE_5,			WB_KEYCODE_6,			// 0
            WB_KEYCODE_7,			WB_KEYCODE_8,			WB_KEYCODE_9,			WB_KEYCODE_0,				WB_KEYCODE_MINUS,	WB_KEYCODE_EQUALS,		WB_KEYCODE_BACKSPACE,	WB_KEYCODE_TAB,			// 0 

            WB_KEYCODE_Q,			WB_KEYCODE_W,			WB_KEYCODE_E,			WB_KEYCODE_R,				WB_KEYCODE_T,		WB_KEYCODE_Y,			WB_KEYCODE_U,			WB_KEYCODE_I,			// 1
            WB_KEYCODE_O,			WB_KEYCODE_P,			WB_KEYCODE_LEFTBRACKET,	WB_KEYCODE_RIGHTBRACKET,	WB_KEYCODE_RETURN,	WB_KEYCODE_LCTRL,		WB_KEYCODE_A,			WB_KEYCODE_S,			// 1 

            WB_KEYCODE_D,			WB_KEYCODE_F,			WB_KEYCODE_G,			WB_KEYCODE_H,				WB_KEYCODE_J,		WB_KEYCODE_K,			WB_KEYCODE_L,			WB_KEYCODE_SEMICOLON,	// 2 
            WB_KEYCODE_APOSTROPHE,	WB_KEYCODE_GRAVE,		WB_KEYCODE_LSHIFT,		WB_KEYCODE_BACKSLASH,		WB_KEYCODE_Z,		WB_KEYCODE_X,			WB_KEYCODE_C,			WB_KEYCODE_V,			// 2 

            WB_KEYCODE_B,			WB_KEYCODE_N,			WB_KEYCODE_M,			WB_KEYCODE_COMMA,			WB_KEYCODE_PERIOD,	WB_KEYCODE_SLASH,		WB_KEYCODE_RSHIFT,		WB_KEYCODE_PRINTSCREEN,// 3
            WB_KEYCODE_LALT,		WB_KEYCODE_SPACE,		WB_KEYCODE_CAPSLOCK,	WB_KEYCODE_F1,				WB_KEYCODE_F2,		WB_KEYCODE_F3,			WB_KEYCODE_F4,			WB_KEYCODE_F5,			// 3 

            WB_KEYCODE_F6,			WB_KEYCODE_F7,			WB_KEYCODE_F8,			WB_KEYCODE_F9,				WB_KEYCODE_F10,		WB_KEYCODE_NUMLOCKCLEAR,WB_KEYCODE_SCROLLLOCK,	WB_KEYCODE_HOME,		// 4
            WB_KEYCODE_UP,			WB_KEYCODE_PAGEUP,		WB_KEYCODE_KP_MINUS,	WB_KEYCODE_LEFT,			WB_KEYCODE_KP_5,	WB_KEYCODE_RIGHT,		WB_KEYCODE_KP_PLUS,		WB_KEYCODE_END,			// 4 

            WB_KEYCODE_DOWN,		WB_KEYCODE_PAGEDOWN,	WB_KEYCODE_INSERT,		WB_KEYCODE_DELETE,			WB_KEYCODE_UNKNOWN,	WB_KEYCODE_UNKNOWN,		WB_KEYCODE_NONUSBACKSLASH,WB_KEYCODE_F11,		// 5
            WB_KEYCODE_F12,			WB_KEYCODE_PAUSE,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_LGUI,			WB_KEYCODE_RGUI,	WB_KEYCODE_APPLICATION,	WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		// 5

            WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,			WB_KEYCODE_UNKNOWN,	WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		// 6
            WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,			WB_KEYCODE_UNKNOWN,	WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		// 6 

            WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,			WB_KEYCODE_UNKNOWN,	WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		// 7
            WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,			WB_KEYCODE_UNKNOWN,	WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN,		WB_KEYCODE_UNKNOWN		// 7 
    };
}