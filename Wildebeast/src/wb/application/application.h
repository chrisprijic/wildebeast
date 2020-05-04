#pragma once

#include "wb/core/core.h"
#include "wb/application/window.h"
#include "wb/events/events.h"
#include "wb/graphics/device_context.h"

namespace wb {
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
			Window* window;
			DeviceContext* graphicsContext;
	};
}

