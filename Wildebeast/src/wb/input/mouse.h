#pragma once

#include <iostream>

namespace wb {
    typedef enum WB_MOUSEBUTTON {
        WB_MOUSEBUTTON_LEFT = 0,
        WB_MOUSEBUTTON_RIGHT,
        WB_MOUSEBUTTON_MIDDLE,
        WB_MOUSEBUTTON_X1,
        WB_MOUSEBUTTON_X2,

        WB_TOTAL_MOUSECODES
    } WB_MOUSEBUTTON;

    inline std::ostream& operator<<(std::ostream& os, WB_MOUSEBUTTON mousecode) {
        os << static_cast<int32_t>(mousecode);
        return os;
    }
}