#pragma once

#include "wb/events/events.h"
#include "wb/application/window.h"

namespace wb {
    class Editor {
    public:
        Editor(Window* window);
        ~Editor();

        void Init();
        void OnUpdate();
        bool OnEvent(Event& e);
    private:
        Window* window;
    };
}
