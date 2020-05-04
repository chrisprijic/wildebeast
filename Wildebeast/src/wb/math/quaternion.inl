#pragma once

#include "wb/math/quaternion.h"

namespace wb {
	// NOTE(Chris): to make sure operators here use our math-defined ones:
	using wb::operator*;
	using wb::operator+;
	using wb::operator-;
	using wb::operator/;
	using wb::operator!=;
	using wb::operator==;
	using wb::lengthSquared;
	using wb::dot;
	using wb::cross;
	using wb::getNorm;

	inline real length(const quat& q) {
		return sqrt(lengthSquared(q.xyz) + q.w * q.w);
	}

	inline real lengthSquared(const quat& q) {
		return (lengthSquared(q.xyz) + q.w * q.w);
	}

	inline real dot(const quat& a, const quat& b) {
		return dot(a.xyz, b.xyz) + a.w * b.w;
	}

	inline quat operator-(const quat& q) {
		return quat{ -q.xyz, -q.w };
	}

	inline quat operator+(const quat& a, const quat& b) {
		return quat{ a.xyz + b.xyz, a.w + b.w };
	}

	inline quat operator-(const quat& a, const quat& b) {
		return quat{ a.xyz - b.xyz, a.w - b.w };
	}

	inline quat operator*(const quat& a, const quat& b) {
		// (v1, s1)(v2, s2) = (v2*s1 + v1*s2 - v1 x v2, s2*s1 - v1 . v2)
		return quat{ (a.v * b.s + b.v * a.s - cross(a.v, b.v)), (a.s * b.s - dot(a.v, b.v)) };
	}

	inline quat operator*(const quat& q, real s) {
		return quat{ q.v * s, q.s * s };
	}

	inline quat operator*(real s, const quat& q) {
		return quat{ q.v * s, q.s * s };
	}

	inline quat operator/(const quat& q, real s) {
		return quat{ q.v / s, q.s / s };
	}

	inline quat operator/(real s, const quat& q) {
		return quat{ q.v / s, q.s / s };
	}

	inline bool operator==(const quat& a, const quat& b) {
		return a.v == b.v && a.w == b.w;
	}

	inline bool operator!=(const quat& a, const quat& b) {
		return a.v != b.v && a.w != b.w;
	}

	inline quat conjugate(const quat& q) {
		return quat{ -q.v, q.s };
	}

	inline quat inverse(const quat& q) {
		return conjugate(q) / lengthSquared(q);
	}

	inline rvec3 operator*(const quat& q, const rvec3& v) {
		rvec3 t = 2.0 * cross(q.v, v);
		return v + q.w * t + cross(q.v, t);
	}

	inline rvec3 operator*(const rvec3& v, const quat& q) {
		rvec3 t = 2.0 * cross(q.v, v);
		return v + q.w * t + cross(q.v, t);
	}

	/**
	 *
	 * Angle's in radians.
	 *
	 */
	inline real angle(const quat& q) {
		return 2.0f * acos(q.w);
	}

	inline rvec3 axis(const quat& q) {
		real sin2 = 1.0f - q.w * q.w;

		if (sin2 < 0.0f) {
			return rvec3{ 0, 0, 1 };
		}

		real invsin2 = 1.0f / sqrt(sin2);

		return q.xyz * invsin2;
	}

	/**
	*
	* Angle's in radians.
	*
	*/
	inline quat quatFromAngleAxis(real angle, const rvec3& axis) {
		rvec3 normaxis = getNorm(axis);

		real s = sin(0.5f * angle);

		return quat{ normaxis * s, cos(0.5f * angle) };
	}

	/**
	*
	* Angle's in radians.
	*
	*/
	inline real roll(const quat& q) {
		return atan2(2.0f * q.x * q.y + q.z * q.w, q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z);
	}

	/**
	*
	* Angle's in radians.
	*
	*/
	inline real pitch(const quat& q) {
		return atan2(2.0f * q.y * q.z + q.w * q.x, q.w * q.w + q.z * q.z - q.y * q.y - q.x * q.x);
	}

	/**
	*
	* Angle's in radians.
	*
	*/
	inline real yaw(const quat& q) {
		return asin(-2.0f * (q.x * q.z - q.w * q.y));
	}

	/**
	*
	* Angle's in radians.
	*
	*/
	inline rvec3 toEuler(const quat& q) {
		return rvec3{ roll(q), pitch(q), yaw(q) };
	}

	inline rmat4 toMat4(const quat& q) {
		rmat4 temp;
		temp.m11 = 1 - 2 * q.y * q.y - 2 * q.z * q.z;
		temp.m12 = 2 * q.x * q.y - 2. * q.z * q.w;
		temp.m13 = 2 * q.z * q.x + 2 * q.y * q.w;
		temp.m14 = 0;
		temp.m21 = 2 * q.x * q.y + 2 * q.z * q.w;
		temp.m22 = 1 - 2 * q.x * q.x - 2 * q.z * q.z;
		temp.m23 = 2 * q.y * q.z - 2 * q.x * q.w;
		temp.m24 = 0;
		temp.m31 = 2 * q.x * q.z - 2 * q.y * q.w;
		temp.m32 = 2 * q.y * q.z + 2 * q.x * q.w;
		temp.m33 = 1 - 2 * q.x * q.x - 2 * q.y * q.y;
		temp.m34 = 0;
		temp.m41 = 0;
		temp.m42 = 0;
		temp.m43 = 0;
		temp.m44 = 1;
		return temp;
	}

	inline quat quatFromMat4(const rmat4& m) {
		const real fourXSquaredMinus1 = m.m11 - m.m22 - m.m33;
		const real fourYSquaredMinus1 = m.m22 - m.m11 - m.m33;
		const real fourZSquaredMinus1 = m.m33 - m.m11 - m.m22;
		const real fourWSquaredMinus1 = m.m11 + m.m22 + m.m33;

		i32 biggestIndex = 0;
		real fourBiggestSquaredMinus1{ fourWSquaredMinus1 };
		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		const real biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
		const real mult = 0.25f / biggestVal;

		quat q = quat{ rvec3{0, 0, 0}, 1 };

		switch (biggestIndex) {
		case 0: {
			q.w = biggestVal;
			q.x = (m.m23 - m.m32) * mult;
			q.y = (m.m31 - m.m13) * mult;
			q.z = (m.m12 - m.m21) * mult;
		}
			  break;
		case 1: {
			q.w = (m.m23 - m.m32) * mult;
			q.x = biggestVal;
			q.y = (m.m12 + m.m21) * mult;
			q.z = (m.m31 + m.m13) * mult;
		}
			  break;
		case 2: {
			q.w = (m.m31 - m.m13) * mult;
			q.x = (m.m12 + m.m21) * mult;
			q.y = biggestVal;
			q.z = (m.m23 + m.m32) * mult;
		}
			  break;
		case 3: {
			q.w = (m.m12 - m.m21) * mult;
			q.x = (m.m31 + m.m13) * mult;
			q.y = (m.m23 + m.m32) * mult;
			q.z = biggestVal;
		}
			  break;
		default: {
			//NOPE
		}
			   break;
		}

		return q;
	}

	inline rmat3 toMat3(const quat& q) {
		rmat3 temp;
		temp.m11 = 1 - 2 * q.y * q.y - 2 * q.z * q.z;
		temp.m12 = 2 * q.x * q.y - 2. * q.z * q.w;
		temp.m13 = 2 * q.z * q.x + 2 * q.y * q.w;
		temp.m21 = 2 * q.x * q.y + 2 * q.z * q.w;
		temp.m22 = 1 - 2 * q.x * q.x - 2 * q.z * q.z;
		temp.m23 = 2 * q.y * q.z - 2 * q.x * q.w;
		temp.m31 = 2 * q.x * q.z - 2 * q.y * q.w;
		temp.m32 = 2 * q.y * q.z + 2 * q.x * q.w;
		temp.m33 = 1 - 2 * q.x * q.x - 2 * q.y * q.y;
		return temp;
	}

	inline quat quatFromMat4(const rmat3& m) {
		const real fourXSquaredMinus1 = m.m11 - m.m22 - m.m33;
		const real fourYSquaredMinus1 = m.m22 - m.m11 - m.m33;
		const real fourZSquaredMinus1 = m.m33 - m.m11 - m.m22;
		const real fourWSquaredMinus1 = m.m11 + m.m22 + m.m33;

		i32 biggestIndex = 0;
		real fourBiggestSquaredMinus1{ fourWSquaredMinus1 };
		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		const real biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
		const real mult = 0.25f / biggestVal;

		quat q = quat{ rvec3{ 0, 0, 0 }, 1 };

		switch (biggestIndex) {
		case 0: {
			q.w = biggestVal;
			q.x = (m.m23 - m.m32) * mult;
			q.y = (m.m31 - m.m13) * mult;
			q.z = (m.m12 - m.m21) * mult;
		} break;
		case 1: {
			q.w = (m.m23 - m.m32) * mult;
			q.x = biggestVal;
			q.y = (m.m12 + m.m21) * mult;
			q.z = (m.m31 + m.m13) * mult;
		} break;
		case 2: {
			q.w = (m.m31 - m.m13) * mult;
			q.x = (m.m12 + m.m21) * mult;
			q.y = biggestVal;
			q.z = (m.m23 + m.m32) * mult;
		} break;
		case 3: {
			q.w = (m.m12 - m.m21) * mult;
			q.x = (m.m31 + m.m13) * mult;
			q.y = (m.m23 + m.m32) * mult;
			q.z = biggestVal;
		} break;
		default: {
			//NOPE
		}
			   break;
		}

		return q;
	}
}