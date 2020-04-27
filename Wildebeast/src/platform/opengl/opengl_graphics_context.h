#pragma once

#include "wb/graphics_context.h"

namespace wb {
	class OpenGLGraphicsContext : public GraphicsContext {
		public:
			virtual void Init() = 0;
			virtual void SwapBuffers() = 0;
			virtual void MakeCurrent() = 0;
			static GraphicsContext* Create(Window* window);
	};
}
