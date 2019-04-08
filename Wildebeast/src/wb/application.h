#pragma once

#include "core.h"

namespace wb {
	class WB_API Application {
	public:
		Application();
		virtual ~Application();

		void run();
	};
}

