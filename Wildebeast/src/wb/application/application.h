#pragma once

#include "wb/core/core.h"
#include "wb/core/platform.h"
#include "wb/application/window.h"
#include "wb/events/events.h"
#include "wb/graphics/device_context.h"
#include "wb/math/math.h"

// ogl
//#include <GL/glew.h>

// d3d12
//#include <d3dx12.h>
//#include <dxgi1_5.h>

// vulkan
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vk_sdk_platform.h>

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
			fmat4 mvp = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
			u32 vao;
			i64 t = 0;

			// NOTE(Chris): TEMP for d3d12 triangle demo
			/*IDXGIFactory5* factory;
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
			D3D12_VERTEX_BUFFER_VIEW vertexBufferView;*/

			// NOTE(Chris): TEMP for vulkan triangle demo
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
	};
}

