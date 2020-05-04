#pragma once

#include "wb/core/types.h"
#include "wb/math/vector.h"
#include "wb/math/matrix.h"
#include "wb/math/quaternion.h"

namespace wb {
	struct Transform {
		rvec3 pos;
		quaternion orientation;
		rvec3 scale;
	};
}

#include "transform.inl"
