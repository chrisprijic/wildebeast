#pragma once

#if !defined(WB_VULKAN) && !defined(WB_DX12) && !defined(WB_OPENGL)
#define WB_OPENGL
#endif

#include "wb/core/core.h"
#include "wb/core/platform.h"
#include "wb/application/window.h"
#include "wb/events/events.h"
#include "wb/graphics/device_context.h"
#include "wb/graphics/render_device.h"
#include "wb/math/math.h"

#ifdef WB_OPENGL
// ogl
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include <GL/glew.h>
#include "platform/opengl/ogl_context.h"
#include "wb/debug/editor.h"
#elif defined(WB_DX12)
// d3d12
#include <d3dx12.h>
#include <dxgi1_5.h>
#elif defined(WB_VULKAN)
// vulkan
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vk_sdk_platform.h>
#endif
namespace wb {
	struct Vertex {
		fvec3 pos;
		fvec4 color;
	};

	struct CB {
		fmat4 MVP;
	};

	struct UBO {
		fmat4 MVP;
	};

    class Application {
        public:
            Application();
            virtual ~Application();

			void Run();
			virtual void OnEvent(Event& e);
			Window* GetWindow() { return window; };
		private:
			void closeWindow();
			void onEvent(Event& e);
		private:
			bool isRunning = true;
			Platform* platform;
			Window* window;

			fmat4 ndc = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			fmat4 mvp = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
			i64 t = 0;
			bool init = false;

			RenderDevice* renderDevice;
			Swapchain* swapchain; 
			u32 frameIndex = 0;

			//std::wstring projectDir = L"C:\\Users\\ChrisPrijic\\Documents\\work\\personal\\wildebeast";
			std::wstring projectDir = L"C:\\Users\\chris\\Documents\\personal\\projects\\project_wildebeast";

#ifdef WB_OPENGL
			// NOTE(Chris): TEMP for ogl triangle demo
			u32 shader_programme;
			i32 mvp_loc;
			
			u32 vao;

			OGLContext* graphicsContext;
			Editor* editor;

#elif defined(WB_DX12)
			ID3D12GraphicsCommandList* cmdList;
			ID3D12DescriptorHeap* rtvHeap;
			ID3D12DescriptorHeap* dsvHeap;
			u32 heapStepSize;
			ID3D12Resource* renderTargets[2];
			ID3D12Resource* depthBuffer;
			ID3D12Fence* fence;
			u32 fenceValue;
			HANDLE fenceEvent;

			ID3D12RootSignature* rootSig;
			ID3D12PipelineState* pipelineState;

			ID3D12Resource* vertexBuffer;
			D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

#elif defined(WB_VULKAN)
			std::vector<VkImageView> RTVs;
			std::vector<VkFramebuffer> RTVFBs;
			VkDescriptorSetLayout descriptorSetLayout;
			VkPipelineLayout pipelineLayout;
			VkRenderPass renderPass;
			VkPipeline graphicsPipeline;
			std::vector<VkCommandBuffer> commandBuffers;
			VkBuffer vertexBuffer;
			VkDeviceMemory vertexBufferMemory;
			std::vector<VkBuffer> uniformBuffers;
			std::vector<VkDeviceMemory> uniformBuffersMemory;
			VkDescriptorPool descriptorPool;
			std::vector<VkDescriptorSet> descriptorSets;
#endif
	};
}

