#pragma once

#ifdef WB_PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#else
	error "Platform unknown"
#endif
#include <vulkan/vulkan.h>
#include <vulkan/vk_sdk_platform.h>


#define VK_CHECK_RESULT(f)											             \
{																	             \
	VkResult res = (f);												             \
	if (res != VK_SUCCESS) {											         \
		WB_CORE_ERROR("VkResult is '{0}' in {1}:{2}", res, __FILE__ , __LINE__); \
		WB_ASSERT(res == VK_SUCCESS)(res);							      		 \
	}																			 \
}
