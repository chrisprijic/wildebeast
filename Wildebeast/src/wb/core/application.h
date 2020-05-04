#pragma once

#include "wb/core/core.h"
#include "wb/core/window.h"
#include "wb/graphics/device_context.h"

namespace wb {
	class Application {
		public:
			Application();
			virtual ~Application();

			void Run();
		private:
			// TODO(Chris): generalize this to window event handling
			void OnWindowClose();
		private:
			bool isRunning = true;
			Window* window;
			DeviceContext* graphicsContext;
	};
}

