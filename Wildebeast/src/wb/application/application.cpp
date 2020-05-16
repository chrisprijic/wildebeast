#include "wbpch.h"

#include "wb/application/application.h"
#include "wb/events/event_router.h"

namespace wb {
    Application::Application() {
        platform = Platform::Create();
        platform->SetEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        platform->Init();

        window = platform->NewWindow();

        CreateDXGIFactory(IID_PPV_ARGS(&factory));
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

        device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator, nullptr, IID_PPV_ARGS(&cmdList));
        cmdList->Close();

        IDXGISwapChain1* tempSwapChain;
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = 1280;
        swapChainDesc.Height = 720;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 2;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        factory->CreateSwapChainForHwnd(cmdQueue, (HWND) window->GetNativeWindow(), &swapChainDesc, nullptr, nullptr, &tempSwapChain);
        swapChain = (IDXGISwapChain3*) tempSwapChain;

        frameIndex = swapChain->GetCurrentBackBufferIndex();


        D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
        heapDesc.NumDescriptors = 2;
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap));
        heapStepSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(heap->GetCPUDescriptorHandleForHeapStart());

        for (u32 n = 0; n < 2; n++) {
            swapChain->GetBuffer(n, IID_PPV_ARGS(&renderTargets[n]));
            device->CreateRenderTargetView(renderTargets[n], nullptr, rtvHandle);
            rtvHandle.Offset(1, heapStepSize);
        }

        device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
        fenceValue = 1;

        fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    }


    Application::~Application() {}

    void Application::OnEvent(Event& e) {}

    void Application::onEvent(Event& e) {
        switch (e.Type) {
            case WB_EVENT_QUIT: {
                closeWindow();
            } break;
            default: {
                OnEvent(e);
            }
        }
    }

    void Application::closeWindow() {
        isRunning = false;
    }

    void Application::Run() {
		while (isRunning) {
			t++;
			platform->OnUpdate();

            mvp.m41 = cos(t / 1000.0);
            mvp.m42 = sin(t / 1000.0);

            cmdAllocator->Reset();
            cmdList->Reset(cmdAllocator, nullptr);

            D3D12_RESOURCE_BARRIER barrier = {};
            barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            barrier.Transition.pResource = renderTargets[frameIndex];
            barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
            barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
            barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

            cmdList->ResourceBarrier(1, &barrier);

            CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(heap->GetCPUDescriptorHandleForHeapStart(), frameIndex, heapStepSize);

            const float color[] = { 0.0f, 0.2f, 0.4f, 1.0f };
            cmdList->ClearRenderTargetView(rtvHandle, color, 0, nullptr);

            barrier = {};
            barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
            barrier.Transition.pResource = renderTargets[frameIndex];
            barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
            barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
            barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

            cmdList->ResourceBarrier(1, &barrier);
            cmdList->Close();

            ID3D12CommandList* ppCmdLists[] = { cmdList };
            cmdQueue->ExecuteCommandLists(_countof(ppCmdLists), ppCmdLists);

			std::cout << '.';

            swapChain->Present(1, 0);

            const u64 cFence = fenceValue;
            cmdQueue->Signal(fence, cFence);
            fenceValue++;

            if (fence->GetCompletedValue() < cFence) {
                fence->SetEventOnCompletion(cFence, fenceEvent);
                WaitForSingleObject(fenceEvent, INFINITE);
            }

            frameIndex = swapChain->GetCurrentBackBufferIndex();
        }
    }
}