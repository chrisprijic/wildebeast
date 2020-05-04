#pragma once

#include <iostream>

namespace wb {
    typedef enum WB_MOUSECODE {
        WB_MOUSEBUTTON_0 = 0,
        WB_MOUSEBUTTON_1,
        WB_MOUSEBUTTON_2,
        WB_MOUSEBUTTON_3,
        WB_MOUSEBUTTON_4,
        WB_MOUSEBUTTON_5,
        WB_MOUSEBUTTON_6,
        WB_MOUSEBUTTON_7,

        WB_MOUSEBUTTON_LAST,
        WB_MOUSEBUTTON_LEFT,
        WB_MOUSEBUTTON_RIGHT,
        WB_MOUSEBUTTON_MIDDLE,


        WB_TOTAL_MOUSECODES
    } WB_MOUSECODE;

    inline std::ostream& operator<<(std::ostream& os, WB_MOUSECODE mousecode) {
        os << static_cast<int32_t>(mousecode);
        return os;
    }
}