#pragma once

#include "wb/core/core.h"
#include "wb/core/platform.h"
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
			Platform* platform;
			Window* window;
			DeviceContext* graphicsContext;

			// NOTE(Chris): TEMP for ogl triangle demo
			u32 shader_programme;
			i32 mvp_loc;
			fmat4 mvp;
			u32 vao;
			i64 t;
	};
}

