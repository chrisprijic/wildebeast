#include "wbpch.h"
#include "platform/dx12/d3d12_swapchain.h"

namespace wb {
    D3D12Swapchain::D3D12Swapchain(IDXGIFactory5* factory, ID3D12CommandQueue* cmdQueue, HWND window) {
        IDXGISwapChain1* tempSwapChain;
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = 1280;
        swapChainDesc.Height = 720;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 2;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        factory->CreateSwapChainForHwnd(cmdQueue, window, &swapChainDesc, nullptr, nullptr, &tempSwapChain);
        swapchain = (IDXGISwapChain3*) tempSwapChain;
    }

    D3D12Swapchain::~D3D12Swapchain() {

    }

    void D3D12Swapchain::Present(u32 vsync) {
        swapchain->Present(0, 0);
    }

    pvoid D3D12Swapchain::GetBuffer(u32 buffer) {
        ID3D12Resource* rt;
        swapchain->GetBuffer(buffer, IID_PPV_ARGS(&rt));
        return rt;
    }

    u32 D3D12Swapchain::GetBackBufferIndex() {
        return swapchain->GetCurrentBackBufferIndex();
    }

    u32 D3D12Swapchain::GetBackBufferCount() {
        return 2;
    }
}