#pragma once

#include "wb/core/core.h"
#include "wb/core/types.h"

#include "wb/input/keyboard.h";
#include "wb/input/mouse.h";

namespace wb {
    class InputManager {
    protected:
        InputManager() = default;
    public:
        static bool IsKeyPressed(u32 keycode);
        static bool IsMouseButtonPressed(u32 buttoncode);
        static float GetMouseX();
        static float GetMouseY();
    private:
        static bool keycodes[WB_TOTAL_KEYCODES];
        static bool mousebuttoncodes[WB_TOTAL_MOUSECODES];
        static float mouseX;
        static float mouseY;
    };
}