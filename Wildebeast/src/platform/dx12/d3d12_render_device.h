#pragma once

#include "wb/graphics/render_device.h";
#include "platform/windows/windows_window.h";

#include <d3dx12.h>
#include <dxgi1_5.h>

namespace wb {
    class D3D12RenderDevice : public RenderDevice {
    public:
        D3D12RenderDevice(Window* window);
        ~D3D12RenderDevice();
        void Init() override;
        pvoid CreateSwapChain() override;
        virtual void Dispatch(pvoid cmdList) override;
        virtual void SignalFence(pvoid fence, u64 fenceValue) override;
        virtual pvoid CreateContext() override;
        virtual void ResetContext(pvoid context) override;
        virtual pvoid getNativeDevice() override;
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
