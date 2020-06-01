#include "wbpch.h"
#include "wb/graphics/render_device.h"
#include "platform/dx12/d3d12_render_device.h"
#include "platform/opengl/ogl_render_device.h"

namespace wb {
    RenderDevice* RenderDevice::Create(RENDERDEVICE_TYPE type, Window* window) {
        switch (type) {
        case WB_RENDERDEVICE_OPENGL: {
            return OGLRenderDevice::Create(window);
        } break;
        case WB_RENDERDEVICE_DIRECTX: {
            return new D3D12RenderDevice(window);
        } break;
        case WB_RENDERDEVICE_VULKAN: {
            return nullptr;
        } break;
        default:
            WB_CORE_ERROR("Render Device is not supported!");
        }
        return nullptr;
    }
}