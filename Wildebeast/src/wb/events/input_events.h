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
}