#pragma once

#include "wb/graphics/render_device.h"
#include "platform/windows/windows_window.h"

#include <d3dx12.h>
#include <dxgi1_5.h>

namespace wb {
    class D3D12RenderDevice : public RenderDevice {
    public:
        D3D12RenderDevice(Window* window);
        ~D3D12RenderDevice();
        void Init() override;
        Swapchain* CreateSwapchain() override;
        virtual void Dispatch(pvoid cmdList) override;
        virtual pvoid CreateContext() override;
        virtual pvoid getNativeDevice() override;

        void SignalFence(pvoid fence, u64 fenceValue);
        void ResetContext(pvoid context);
    private:
        WindowsWindow* window;
        
        // d3d12 resources
        IDXGIFactory5* factory;
        IDXGIAdapter1* adapter;
        ID3D12Debug* debugController;
        ID3D12Device* device;
        ID3D12CommandQueue* cmdQueue;
        ID3D12CommandAllocator* cmdAllocator;
        IDXGISwapChain3* swapChain;
    };
}
