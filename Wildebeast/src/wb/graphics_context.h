#pragma once

#include "wb/window.h"

namespace wb {

	enum GRAPHICS_CONTEXT_TYPE {
		WB_GC_NONE   = 0,
		WB_GC_OPENGL = 1
	};

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void MakeCurrent() = 0;

		static GraphicsContext* Create(GRAPHICS_CONTEXT_TYPE type, Window* window);
	};

}