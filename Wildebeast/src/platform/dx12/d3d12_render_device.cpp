#include "wbpch.h"
#include "platform/dx12/d3d12_render_device.h"
#include "platform/dx12/d3d12_swapchain.h"

namespace wb {
    D3D12RenderDevice::D3D12RenderDevice(Window* window) {
        this->window = (WindowsWindow*) window;
    }

    D3D12RenderDevice::~D3D12RenderDevice() {
        // TODO(Chris): cleanup here
    }

    void D3D12RenderDevice::Init() {
        D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
        debugController->EnableDebugLayer();
        u32 dxgiFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;

        CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));
        for (UINT adapterIndex = 0;; adapterIndex++) {
            if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &adapter)) {
                break;
            }

            if (SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, __uuidof(ID3D12Device), nullptr))) {
                break;
            }
        }

        D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device));

        D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
        device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue));

        device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator));
    }

    Swapchain* D3D12RenderDevice::CreateSwapchain() {
        return new D3D12Swapchain(factory, cmdQueue, (HWND) window->GetNativeWindow());
    }

    void D3D12RenderDevice::Dispatch(pvoid cmdList) {
        ID3D12CommandList* ppCmdLists[] = { (ID3D12GraphicsCommandList*)cmdList };
        cmdQueue->ExecuteCommandLists(_countof(ppCmdLists), ppCmdLists);
    }

    void D3D12RenderDevice::SignalFence(pvoid fence, u64 fenceValue) {
        cmdQueue->Signal((ID3D12Fence*)fence, fenceValue);
    }

    pvoid D3D12RenderDevice::CreateContext() {
        ID3D12GraphicsCommandList* cmdList;
        device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator, nullptr, IID_PPV_ARGS(&cmdList));
        cmdList->Close();

        return cmdList;
    }

    void D3D12RenderDevice::ResetContext(pvoid context) {
        ID3D12GraphicsCommandList* cmdList = (ID3D12GraphicsCommandList*) context;
        cmdAllocator->Reset();
        cmdList->Reset(cmdAllocator, nullptr);
    }

    pvoid D3D12RenderDevice::getNativeDevice() {
        return device;
    }
}