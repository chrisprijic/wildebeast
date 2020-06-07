#pragma once

#include "wb/application/window.h"

namespace wb {
    class OGLContext {
        public:
            virtual bool Init() = 0;
            virtual void SetVSync(bool enabled) = 0;
            virtual void SwapBuffers() = 0;
            virtual void MakeCurrent() = 0;
            static OGLContext* Create(Window* window);
    };
}
