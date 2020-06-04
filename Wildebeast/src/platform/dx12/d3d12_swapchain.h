#pragma once

#include "platform/dx12/base.h"
#include "wb/graphics/swapchain.h"

namespace wb {
    class D3D12Swapchain : public Swapchain {
    public:
        D3D12Swapchain(IDXGIFactory5* factory, ID3D12CommandQueue* cmdQueue, HWND window);
        ~D3D12Swapchain();
        virtual void Present(u32 vsync) override;
        virtual pvoid GetBuffer(u32 buffer) override;
        virtual u32 GetBackBufferIndex() override;
        virtual u32 GetBackBufferCount() override;
    private:
        IDXGISwapChain3* swapchain;
    };
}
