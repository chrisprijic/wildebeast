#pragma once

#include "wb/math/transform.h"

namespace wb {
	// NOTE(Chris): to make sure operators here use our math-defined ones:
	using wb::operator*;
	using wb::operator+;
	using wb::operator-;
	using wb::operator/;

	inline Transform& operator*(const Transform& ps, const Transform& ls) {
		Transform ws;

		ws.pos = ps.pos + ps.orientation * (ps.scale * ls.pos);
		ws.orientation = ps.orientation * ls.orientation;
		ws.scale = ps.scale * ps.orientation * ls.scale;

		return ws;
	}

	inline Transform& operator/(const Transform& ws, const Transform& ps) {
		Transform ls;

		const quaternion psConjugate = conjugate(ps.orientation);

		ls.pos = psConjugate * (ws.pos - ps.pos) / ps.scale;
		ls.orientation = psConjugate * ws.orientation;
		ls.scale = psConjugate * (ws.scale / ps.scale);

		return ls;
	}

	inline rvec3& operator*(const Transform& transform, const rvec3& point)
	{
		return (conjugate(transform.orientation) * (transform.pos + point)) / transform.scale;
	}

	inline Transform inverse(const Transform& t)
	{
		const quaternion invOrientation = conjugate(t.orientation);

		Transform invTransform;

		invTransform.pos = (invOrientation * -t.pos) / t.scale;
		invTransform.orientation = invOrientation;
		invTransform.scale = invOrientation * (rvec3{ 1, 1, 1 } / t.scale);

		return invTransform;
	}
}