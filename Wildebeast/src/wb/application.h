#pragma once

#include "wb/core.h"
#include "wb/window.h"

namespace wb {
	class Application {
		public:
			Application();
			virtual ~Application();

			void Run();
		private:
			void OnWindowClose();
		private:
			bool isRunning = true;
			Window* window;
	};
}

