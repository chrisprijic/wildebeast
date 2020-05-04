#pragma once

#include "wb/application/window.h"

namespace wb {

    enum DEVICE_CONTEXT_TYPE {
        WB_DEVICECONTEXT_NONE   = 0,
        WB_DEVICECONTEXT_OPENGL
    };

    class DeviceContext
    {
    public:
        virtual bool Init() = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual void SwapBuffers() = 0;
        virtual void MakeCurrent() = 0;

        static DeviceContext* Create(DEVICE_CONTEXT_TYPE type, Window* window);
    };

}