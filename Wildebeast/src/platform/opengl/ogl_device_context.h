#pragma once

#include "wb/device_context.h"

namespace wb {
	class OGLDeviceContext : public DeviceContext {
		public:
			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;
			virtual void MakeCurrent() = 0;
			static DeviceContext* Create(Window* window);
	};
}