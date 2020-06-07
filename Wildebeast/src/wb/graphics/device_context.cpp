#include "wbpch.h"
#include "wb/graphics/device_context.h"
//#include "platform/opengl/ogl_device_context.h"

namespace wb {
    DeviceContext* DeviceContext::Create(DEVICE_CONTEXT_TYPE type, Window* window) {
        switch (type) {
            //case WB_DEVICECONTEXT_OPENGL: {
            //    return OGLDeviceContext::Create(window);
            //} break;
            default:
                WB_CORE_ERROR("Graphics Context is not supported!");
        }
        return nullptr;
    }
}