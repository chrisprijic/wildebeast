#pragma once

#include "wb/core/types.h"
#include "wb/math/vector.h"
#include "wb/math/matrix.h"

namespace wb {
	union quat {
		struct {
			rvec3 v;
			real s;
		};
		struct {
			real x, y, z, w;
		};
		struct {
			rvec3 xyz;
		};
		real data[4];
	};

	typedef quat quaternion;
}

#include "quaternion.inl"