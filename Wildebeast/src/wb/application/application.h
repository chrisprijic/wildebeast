#pragma once

#if !defined(WB_VULKAN) && !defined(WB_DX12) && !defined(WB_OGL)
#define WB_OGL
#endif

#include "wb/core/core.h"
#include "wb/core/platform.h"
#include "wb/application/window.h"
#include "wb/events/events.h"
#include "wb/graphics/device_context.h"
#include "wb/math/math.h"

#ifdef WB_OGL
// ogl
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include <GL/glew.h>
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
			DeviceContext* graphicsContext;

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
#ifdef WB_OGL
			// NOTE(Chris): TEMP for ogl triangle demo
			u32 shader_programme;
			i32 mvp_loc;

			u32 vao;

			Editor* editor;

#elif defined(WB_DX12)
			IDXGIFactory5* factory;
			IDXGIAdapter1* adapter;
			ID3D12Debug* debugController;
			ID3D12Device* device;
			ID3D12CommandQueue* cmdQueue;
			ID3D12CommandAllocator* cmdAllocator;
			ID3D12GraphicsCommandList* cmdList;
			IDXGISwapChain3* swapChain;
			ID3D12DescriptorHeap* rtvHeap;
			ID3D12DescriptorHeap* dsvHeap;
			u32 frameIndex;
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
			VkInstance instance;
			VkDebugUtilsMessengerEXT debugMessenger;
			VkPhysicalDevice physicalDevice;
			std::vector<const char*> physicalDeviceExtensions;
			u32 queueFamily = 0;
			VkDevice device;
			VkQueue queue;
			VkSurfaceKHR surface;
			VkSwapchainKHR swapChain;
			std::vector<VkImage> swapChainImages;
			std::vector<VkImageView> RTVs;
			std::vector<VkFramebuffer> RTVFBs;
			VkFormat rtvFormat;
			VkDescriptorSetLayout descriptorSetLayout;
			VkPipelineLayout pipelineLayout;
			VkRenderPass renderPass;
			VkPipeline graphicsPipeline;
			VkCommandPool commandPool;
			std::vector<VkCommandBuffer> commandBuffers;
			VkSemaphore imageAvailableSemaphore;
			VkSemaphore renderFinishedSemaphore;
			u32 frameIndex = 0;
			VkBuffer vertexBuffer;
			VkDeviceMemory vertexBufferMemory;
			std::vector<VkBuffer> uniformBuffers;
			std::vector<VkDeviceMemory> uniformBuffersMemory;
			VkDescriptorPool descriptorPool;
			std::vector<VkDescriptorSet> descriptorSets;
#endif
	};
}

