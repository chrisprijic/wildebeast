#include "wbpch.h"

#include "wb/application/application.h"
#ifdef WB_DX12
#include "wb/events/event_router.h"
#include "platform/dx12/d3d12_render_device.h"

#include <D3Dcompiler.h>

namespace wb {
    Application::Application() {
        platform = Platform::Create();
        platform->SetEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        platform->Init();

        window = platform->NewWindow();

        renderDevice = RenderDevice::Create(WB_RENDERDEVICE_DIRECTX, window);
        renderDevice->Init();

        ID3D12Device* device = (ID3D12Device*)renderDevice->getNativeDevice();

        swapchain = renderDevice->CreateSwapchain();

        cmdList = (ID3D12GraphicsCommandList*) renderDevice->CreateContext();
        cmdList->Close();

        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
        rtvHeapDesc.NumDescriptors = 2;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
        heapStepSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());

        for (u32 n = 0; n < 2; n++) {
            renderTargets[n] = (ID3D12Resource*)swapchain->GetBuffer(n);
            device->CreateRenderTargetView(renderTargets[n], nullptr, rtvHandle);
            rtvHandle.Offset(1, heapStepSize);
        }

        D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
        dsvHeapDesc.NumDescriptors = 1;
        dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

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

        HRESULT hr = D3DCompileFromFile((projectDir + (L"\\assets\\vertex.hlsl")).c_str() , nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &vertexShader, &error);
        if (FAILED(hr)) {
            OutputDebugStringA((char*) error->GetBufferPointer());
        }

        hr = D3DCompileFromFile((projectDir + (L"\\assets\\pixel.hlsl")).c_str(), nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &pixelShader, &error);
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
        psoDesc.DepthStencilState.DepthEnable = TRUE;
        psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
        psoDesc.DepthStencilState.StencilEnable = FALSE;
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
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

        D3D12_CLEAR_VALUE optimizedClearValue = {};
        optimizedClearValue.Format = DXGI_FORMAT_D32_FLOAT;
        optimizedClearValue.DepthStencil = { 1.0f, 0 };

        device->CreateCommittedResource(
            &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
            D3D12_HEAP_FLAG_NONE,
            &CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, 1280, 720,
                1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
            D3D12_RESOURCE_STATE_DEPTH_WRITE,
            &optimizedClearValue,
            IID_PPV_ARGS(&depthBuffer));

        D3D12_DEPTH_STENCIL_VIEW_DESC dsv = {};
        dsv.Format = DXGI_FORMAT_D32_FLOAT;
        dsv.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        dsv.Texture2D.MipSlice = 0;
        dsv.Flags = D3D12_DSV_FLAG_NONE;

        device->CreateDepthStencilView(depthBuffer, &dsv,
            dsvHeap->GetCPUDescriptorHandleForHeapStart());
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
            frameIndex = swapchain->GetBackBufferIndex();
			t++;
			platform->OnUpdate();

            mvp.m41 = cos(t / 1000.0);
            mvp.m42 = sin(t / 1000.0);

            const u64 cFence = fenceValue;
            ((D3D12RenderDevice*)renderDevice)->SignalFence(fence, cFence);
            fenceValue++;

            if (fence->GetCompletedValue() < cFence) {
                fence->SetEventOnCompletion(cFence, fenceEvent);
                WaitForSingleObject(fenceEvent, INFINITE);
            }

            ((D3D12RenderDevice*) renderDevice)->ResetContext(cmdList);

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

            CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, heapStepSize);

            const float color[] = { 0.0f, 0.2f, 0.4f, 1.0f };
            cmdList->ClearRenderTargetView(rtvHandle, color, 0, nullptr);

            D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
            cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1, 0, 0, nullptr);

            cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            cmdList->IASetVertexBuffers(0, 1, &vertexBufferView);
            CB cb = CB{ mvp * ndc };
            cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);
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

            renderDevice->Dispatch(cmdList);

			std::cout << '.';

            swapchain->Present(false);
        }
    }
}
#endif