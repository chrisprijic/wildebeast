#pragma once

#include "wb/core/core.h"
#include "wb/core/platform.h"
#include "wb/application/window.h"
#include "wb/events/events.h"
#include "wb/graphics/device_context.h"
#include "wb/math/math.h"

#include <d3dx12.h>
#include <dxgi1_5.h>

namespace wb {
	struct Vertex {
		fvec3 pos;
		fvec4 color;
	};

    class Application {
        public:
            Application();
            virtual ~Application();

			void Run();
			virtual void OnEvent(Event& e);
		private:
			void closeWindow();
			void onEvent(Event& e);
		private:
			bool isRunning = true;
			Platform* platform;
			Window* window;
			DeviceContext* graphicsContext;

			// NOTE(Chris): TEMP for ogl triangle demo
			u32 shader_programme;
			i32 mvp_loc;
			fmat4 mvp;
			u32 vao;
			i64 t;

			//NOTE(Chris): TEMP for d3d12 triangle demo
			IDXGIFactory5* factory;
			IDXGIAdapter1* adapter;
			ID3D12Device* device;
			ID3D12CommandQueue* cmdQueue;
			ID3D12CommandAllocator* cmdAllocator;
			ID3D12GraphicsCommandList* cmdList;
			IDXGISwapChain3* swapChain;
			ID3D12DescriptorHeap* heap;
			u32 frameIndex;
			u32 heapStepSize;
			ID3D12Resource* renderTargets[2];
			ID3D12Fence* fence;
			u32 fenceValue;
			HANDLE fenceEvent;

			ID3D12RootSignature* rootSig;
			ID3D12PipelineState* pipelineState;

			ID3D12Resource* vertexBuffer;
			D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	};
}

