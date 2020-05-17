#include "wbpch.h"

#include "wb/application/application.h"
#include "wb/events/event_router.h"

#include <D3Dcompiler.h>

namespace wb {
    Application::Application() {
        platform = Platform::Create();
        platform->SetEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        platform->Init();

        window = platform->NewWindow();

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

        CD3DX12_ROOT_PARAMETER1 rootParameters[1];
        rootParameters[0].InitAsConstants(sizeof(fmat4) / 4, 0, 0, D3D12_SHADER_VISIBILITY_VERTEX);

        CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;

        D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
            D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
            D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

        rootSignatureDesc.Init_1_1(_countof(rootParameters), rootParameters, 0, nullptr, rootSignatureFlags);
        ID3DBlob* signature;
        ID3DBlob* error;
        HRESULT res = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_1, &signature, &error);

        device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSig));

        ID3DBlob* vertexShader;
        ID3DBlob* pixelShader;

        HRESULT hr = D3DCompileFromFile(L"C:\\Users\\ChrisPrijic\\Documents\\work\\personal\\wildebeast\\assets\\vertex.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &vertexShader, &error);
        if (FAILED(hr)) {
            OutputDebugStringA((char*) error->GetBufferPointer());
        }

        hr = D3DCompileFromFile(L"C:\\Users\\ChrisPrijic\\Documents\\work\\personal\\wildebeast\\assets\\pixel.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &pixelShader, &error);
        if (FAILED(hr)) {
            OutputDebugStringA((char*) error->GetBufferPointer());
        }

        D3D12_INPUT_ELEMENT_DESC inputElementDescs[] = {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
        };

        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
        psoDesc.pRootSignature = rootSig;
        psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader);
        psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader);
        psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
        psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        psoDesc.DepthStencilState.DepthEnable = FALSE;
        psoDesc.DepthStencilState.StencilEnable = FALSE;
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.SampleDesc.Count = 1;
        device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState));

        Vertex points[] = {
            {{  0.00f,  0.25f,  0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }},
            {{  0.25f, -0.25f,  0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }},
            {{ -0.25f, -0.25f,  0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }}
        };

        const u32 vertexBufferSize = sizeof(points);

        device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexBuffer));
        pu8 pVertexDataBegin;
        CD3DX12_RANGE readRange(0, 0);
        vertexBuffer->Map(0, &readRange, (void**) (&pVertexDataBegin));
        memcpy(pVertexDataBegin, points, vertexBufferSize);
        vertexBuffer->Unmap(0, nullptr);

        vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
        vertexBufferView.StrideInBytes = sizeof(Vertex);
        vertexBufferView.SizeInBytes = vertexBufferSize;

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

            mvp.m14 = cos(t / 1000.0);
            mvp.m24 = sin(t / 1000.0);

            const u64 cFence = fenceValue;
            cmdQueue->Signal(fence, cFence);
            fenceValue++;

            if (fence->GetCompletedValue() < cFence) {
                fence->SetEventOnCompletion(cFence, fenceEvent);
                WaitForSingleObject(fenceEvent, INFINITE);
            }

            cmdAllocator->Reset();
            cmdList->Reset(cmdAllocator, pipelineState);

            cmdList->SetGraphicsRootSignature(rootSig);
            cmdList->SetPipelineState(pipelineState);
            cmdList->RSSetViewports(1, &CD3DX12_VIEWPORT(0.0f, 0.0f, 1280.0f, 720.0f));
            cmdList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, 1280, 720));

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
            cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            cmdList->IASetVertexBuffers(0, 1, &vertexBufferView);
            CB cb = CB{ mvp };
            cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
            cmdList->SetGraphicsRoot32BitConstants(0, sizeof(fmat4) / 4, &cb, 0);
            cmdList->DrawInstanced(3, 1, 0, 0);

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

            swapChain->Present(0, 0);

            frameIndex = swapChain->GetCurrentBackBufferIndex();
        }
    }
}