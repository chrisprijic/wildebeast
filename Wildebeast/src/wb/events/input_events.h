#pragma once

#include "wb/core/types.h"

namespace wb {
    typedef struct KeyboardEvent {
        u32 Type;
        u32 Timestamp;
        u32 WindowID;
        u8  Code;
    } KeyboardEvent;

    typedef struct MouseButtonEvent {
        u32 Type;
        u32 Timestamp;
        u32 WindowID;
        u8  Code;
        i32 X;
        i32 Y;
    } MouseButtonEvent;

    typedef struct MouseMoveEvent {
        u32 Type;
        u32 Timestamp;
        u32 WindowID;
        u8  padding1;
        i32 X;
        i32 Y;
    } MouseMoveEvent;

    typedef struct MouseScrollEvent {
        u32 Type;
        u32 Timestamp;
        u32 WindowID;
        u8  padding1;
        i32 X;
        i32 Y;
    } MouseScrollEvent; 
    
    typedef struct GamepadEvent {
        u32 Type;
        u32 Timestamp;
        u32 WindowID;
        u8 padding1;
        i16 LX;
        i16 LY;
        i16 RX;
        i16 RY;
        u8 LT;
        u8 RT;
        u8 DPAD;
        u8 FPAD;
        u8 AuxButtons;
    } GamepadEvent;
}