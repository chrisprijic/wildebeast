#pragma once

#include "wb/math/matrix.h"
#include "wb/math/vector.h"

namespace wb {
	template<typename T>
	inline bool operator==(const mat2<T>& m, const mat2<T>& rhs) {
		for (int i = 0; i < 4; i++) {
			if (m.data[i] != rhs[i]) {
				return false;
			}
		}
		return true;
	}
	template<typename T>
	inline bool operator!=(const mat2<T>& m, const mat2<T>& rhs) {
		for (int i = 0; i < 4; i++) {
			if (m.data[i] != rhs[i]) {
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline mat2<T>& operator*=(mat2<T>& m, T a) {
		m.m11* (a);
		m.m12* (a);
		m.m21* (a);
		m.m22* (a);
		return m;
	}

	template<typename T>
	inline mat2<T>& operator/=(mat2<T>& m, T a) {
		m.m11 / (a);
		m.m12 / (a);
		m.m21 / (a);
		m.m22 / (a);
		return m;
	}

	template<typename T>
	inline mat2<T>& operator*=(mat2<T>& m, const mat2<T>& other) {
		mat2<T> temp;
		temp.m11 = m.m11 * other.m11 + m.m12 * other.m21;
		temp.m12 = m.m11 * other.m12 + m.m12 * other.m22;
		temp.m21 = m.m21 * other.m11 + m.m22 * other.m21;
		temp.m22 = m.m21 * other.m12 + m.m22 * other.m22;
		m = temp;
		return m;
	}

	template<typename T>
	inline vec2<T> operator*(const mat2<T>& m, const vec2<T>& v) {
		return vec2<T>{m.m11* v.x + m.m12 * v.y, m.m21* v.x + m.m22 * v.y};
	}

	template<typename T>
	inline vec2<T> operator*(const vec2<T>& v, const mat2<T>& m) {
		return vec2<T>{m.m11* v.x + m.m21 * v.y, m.m12* v.x + m.m22 * v.y};
	}

	template<typename T>
	inline mat2<T> operator*(const T a, const mat2<T>& m) {
		return mat2<T>{m.m11* a, m.m21* a, m.m12* a, m.m22* a};
	}

	template<typename T>
	inline mat2<T> operator*(const mat2<T>& m, const T a) {
		return mat2<T>{m.m11* a, m.m21* a, m.m12* a, m.m22* a};
	}

	template<typename T>
	inline mat2<T> operator*(const mat2<T>& a, const mat2<T>& b) {
		return mat2<T>{
			a.m11* b.m11 + a.m12 * b.m21,
				a.m21* b.m11 + a.m22 * b.m21,
				a.m11* b.m12 + a.m12 * b.m22,
				a.m21* b.m12 + a.m22 * b.m22
		};
	}

	template<typename T>
	inline mat2<T> operator/(const T a, const mat2<T>& m) {
		return mat2<T>{m.m11 / a, m.m21 / a, m.m12 / a, m.m22 / a};
	}

	template<typename T>
	inline mat2<T> operator/(const mat2<T>& m, const T a) {
		return mat2<T>{m.m11 / a, m.m21 / a, m.m12 / a, m.m22 / a};
	}

	template<typename T>
	inline mat2<T> operator~(const mat2<T>& m) {
		return mat2<T>(~m.m11, ~m.m12, ~m.m21, ~m.m22);
	}

	template<typename T>
	inline mat2<T> operator-(const mat2<T>& m) {
		return mat2<T>(-m.m11, -m.m12, -m.m21, -m.m22);
	}

	template <typename T>
	inline const T* glPtr(const mat2<T>& m) {
		return reinterpret_cast<const T*>(&m);
	}

	/************************************************************************/
	/* mat3 Implementation                                                  */
	/************************************************************************/
	template<typename T>
	inline bool operator==(const mat3<T>& m, const mat3<T>& rhs) {
		for (int i = 0; i < 9; i++) {
			if (m.data[i] != rhs[i]) {
				return false;
			}
		}
		return true;
	}
	template<typename T>
	inline bool operator!=(const mat3<T>& m, const mat3<T>& rhs) {
		for (int i = 0; i < 9; i++) {
			if (m.data[i] != rhs[i]) {
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline mat3<T>& operator*=(mat3<T>& m, T a) {
		m.m11* (a);
		m.m12* (a);
		m.m13* (a);
		m.m21* (a);
		m.m22* (a);
		m.m23* (a);
		m.m31* (a);
		m.m32* (a);
		m.m33* (a);
		return m;
	}

	template<typename T>
	inline mat3<T>& operator/=(mat3<T>& m, T a) {
		m.m11 / (a);
		m.m12 / (a);
		m.m13 / (a);
		m.m21 / (a);
		m.m22 / (a);
		m.m23 / (a);
		m.m31 / (a);
		m.m32 / (a);
		m.m33 / (a);
		return m;
	}
	template<typename T>
	inline mat3<T>& operator*=(mat3<T>& m, const mat3<T>& other) {
		mat3<T> temp;
		temp.m11 = m.m11 * other.m11 + m.m12 * other.m21 + m.m13 * other.m31;
		temp.m12 = m.m11 * other.m12 + m.m12 * other.m22 + m.m13 * other.m32;
		temp.m13 = m.m11 * other.m13 + m.m12 * other.m23 + m.m13 * other.m33;
		temp.m21 = m.m21 * other.m11 + m.m22 * other.m21 + m.m23 * other.m31;
		temp.m22 = m.m21 * other.m12 + m.m22 * other.m22 + m.m23 * other.m32;
		temp.m23 = m.m21 * other.m13 + m.m22 * other.m23 + m.m23 * other.m33;
		temp.m31 = m.m31 * other.m11 + m.m32 * other.m21 + m.m33 * other.m31;
		temp.m32 = m.m31 * other.m12 + m.m32 * other.m22 + m.m33 * other.m32;
		temp.m33 = m.m31 * other.m13 + m.m32 * other.m23 + m.m33 * other.m33;
		m = temp;
		return m;
	}

	template<typename T>
	inline vec3<T> operator*(const mat3<T>& m, const vec3<T>& v) {
		return vec3<T>{
			m.m11* v.x + m.m12 * v.y * m.m13 * v.z,
				m.m21* v.x + m.m22 * v.y * m.m23 * v.z,
				m.m31* v.x + m.m32 * v.y * m.m33 * v.z
		};
	}

	template<typename T>
	inline vec3<T> operator*(const vec3<T>& v, const mat3<T>& m) {
		return vec3<T>{
			m.m11* v.x + m.m21 * v.y * m.m31 * v.z,
				m.m12* v.x + m.m22 * v.y * m.m32 * v.z,
				m.m13* v.x + m.m23 * v.y * m.m33 * v.z
		};
	}

	template<typename T>
	inline mat3<T> operator*(const T a, const mat3<T>& m) {
		return mat3<T>{
			m.m11* a, m.m21* a, m.m31* a,
				m.m12* a, m.m22* a, m.m32* a,
				m.m13* a, m.m23* a, m.m33* a
		};
	}

	template<typename T>
	inline mat3<T> operator*(const mat3<T>& m, const T a) {
		return mat3<T>{
			m.m11* a, m.m21* a, m.m31* a,
				m.m12* a, m.m22* a, m.m32* a,
				m.m13* a, m.m23* a, m.m33* a
		};
	}

	template<typename T>
	inline mat3<T> operator*(const mat3<T>& m, const mat3<T>& other) {
		mat3<T> temp;
		temp.m11 = m.m11 * other.m11 + m.m12 * other.m21 + m.m13 * other.m31;
		temp.m12 = m.m11 * other.m12 + m.m12 * other.m22 + m.m13 * other.m32;
		temp.m13 = m.m11 * other.m13 + m.m12 * other.m23 + m.m13 * other.m33;
		temp.m21 = m.m21 * other.m11 + m.m22 * other.m21 + m.m23 * other.m31;
		temp.m22 = m.m21 * other.m12 + m.m22 * other.m22 + m.m23 * other.m32;
		temp.m23 = m.m21 * other.m13 + m.m22 * other.m23 + m.m23 * other.m33;
		temp.m31 = m.m31 * other.m11 + m.m32 * other.m21 + m.m33 * other.m31;
		temp.m32 = m.m31 * other.m12 + m.m32 * other.m22 + m.m33 * other.m32;
		temp.m33 = m.m31 * other.m13 + m.m32 * other.m23 + m.m33 * other.m33;
		return temp;
	}

	template<typename T>
	inline mat3<T> operator/(const T a, const mat3<T>& m) {
		return mat3<T>{
			m.m11 / a, m.m21 / a, m.m31 / a,
				m.m12 / a, m.m22 / a, m.m32 / a,
				m.m13 / a, m.m23 / a, m.m33 / a
		};
	}

	template<typename T>
	inline mat3<T> operator/(const mat3<T>& m, const T a) {
		return mat3<T>{
			m.m11 / a, m.m21 / a, m.m31 / a,
				m.m12 / a, m.m22 / a, m.m32 / a,
				m.m13 / a, m.m23 / a, m.m33 / a
		};
	}

	template<typename T>
	inline mat3<T> operator~(const mat3<T>& m) {
		return mat3<T>{
			~m.m11, ~m.m21, ~m.m31,
				~m.m12, ~m.m22m ~m.m32,
				~m.m13, ~m.m23, ~m.m33
		};
	}

	template<typename T>
	inline mat3<T> operator-(const mat3<T>& m) {
		return mat3<T>{
			-m.m11, -m.m21, -m.m31,
				-m.m12, -m.m22m - m.m32,
				-m.m13, -m.m23, -m.m33
		};
	}

	template <typename T>
	inline const T* glPtr(const mat3<T>& m) {
		return reinterpret_cast<const T*>(&m);
	}

	/************************************************************************/
	/* mat4 Implementation                                                  */
	/************************************************************************/
	template<typename T>
	inline bool operator==(const mat4<T>& m, const mat4<T>& rhs) {
		for (int i = 0; i < 16; i++) {
			if (m.data[i] != rhs[i]) {
				return false;
			}
		}
		return true;
	}
	template<typename T>
	inline bool operator!=(const mat4<T>& m, const mat4<T>& rhs) {
		for (int i = 0; i < 16; i++) {
			if (m.data[i] != rhs[i]) {
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline mat4<T>& operator*=(mat4<T>& m, T a) {
		m.m11* (a);
		m.m12* (a);
		m.m13* (a);
		m.m14* (a);
		m.m21* (a);
		m.m22* (a);
		m.m23* (a);
		m.m24* (a);
		m.m31* (a);
		m.m32* (a);
		m.m33* (a);
		m.m34* (a);
		m.m41* (a);
		m.m42* (a);
		m.m43* (a);
		m.m44* (a);
		return m;
	}

	template<typename T>
	inline mat4<T>& operator/=(mat4<T>& m, T a) {
		m.m11 / (a);
		m.m12 / (a);
		m.m13 / (a);
		m.m14 / (a);
		m.m21 / (a);
		m.m22 / (a);
		m.m23 / (a);
		m.m24 / (a);
		m.m31 / (a);
		m.m32 / (a);
		m.m33 / (a);
		m.m34 / (a);
		m.m41 / (a);
		m.m42 / (a);
		m.m43 / (a);
		m.m44 / (a);
		return m;
	}
	template<typename T>
	inline mat4<T>& operator*=(mat4<T>& m, const mat4<T>& other) {
		mat4<T> temp;
		temp.m11 = m.m11 * other.m11 + m.m12 * other.m21 + m.m13 * other.m31 + m.m14 * other.m41;
		temp.m12 = m.m11 * other.m12 + m.m12 * other.m22 + m.m13 * other.m32 + m.m14 * other.m42;
		temp.m13 = m.m11 * other.m13 + m.m12 * other.m23 + m.m13 * other.m33 + m.m14 * other.m43;
		temp.m14 = m.m11 * other.m14 + m.m12 * other.m24 + m.m13 * other.m34 + m.m14 * other.m44;
		temp.m21 = m.m21 * other.m11 + m.m22 * other.m21 + m.m23 * other.m31 + m.m24 * other.m41;
		temp.m22 = m.m21 * other.m12 + m.m22 * other.m22 + m.m23 * other.m32 + m.m24 * other.m42;
		temp.m23 = m.m21 * other.m13 + m.m22 * other.m23 + m.m23 * other.m33 + m.m24 * other.m43;
		temp.m24 = m.m21 * other.m14 + m.m22 * other.m24 + m.m23 * other.m34 + m.m24 * other.m44;
		temp.m31 = m.m31 * other.m11 + m.m32 * other.m21 + m.m33 * other.m31 + m.m34 * other.m41;
		temp.m32 = m.m31 * other.m12 + m.m32 * other.m22 + m.m33 * other.m32 + m.m34 * other.m42;
		temp.m33 = m.m31 * other.m13 + m.m32 * other.m23 + m.m33 * other.m33 + m.m34 * other.m43;
		temp.m34 = m.m31 * other.m14 + m.m32 * other.m24 + m.m33 * other.m34 + m.m34 * other.m44;
		temp.m41 = m.m41 * other.m11 + m.m42 * other.m21 + m.m43 * other.m31 + m.m44 * other.m41;
		temp.m42 = m.m41 * other.m12 + m.m42 * other.m22 + m.m43 * other.m32 + m.m44 * other.m42;
		temp.m43 = m.m41 * other.m13 + m.m42 * other.m23 + m.m43 * other.m33 + m.m44 * other.m43;
		temp.m44 = m.m41 * other.m14 + m.m42 * other.m24 + m.m43 * other.m34 + m.m44 * other.m44;

		m = temp;
		return m;
	}

	template<typename T>
	inline vec4<T> operator*(const mat4<T>& m, const vec4<T>& v) {
		return vec4<T>{
			m.m11* v.x + m.m12 * v.y * m.m13 * v.z + m.m14 * v.w,
				m.m21* v.x + m.m22 * v.y * m.m23 * v.z + m.m24 * v.w,
				m.m31* v.x + m.m32 * v.y * m.m33 * v.z + m.m34 * v.w,
				m.m41* v.x + m.m42 * v.y * m.m43 * v.z + m.m44 * v.w
		};
	}

	template<typename T>
	inline vec4<T> operator*(const vec4<T>& v, const mat4<T>& m) {
		return vec4<T>{
			m.m11* v.x + m.m21 * v.y * m.m31 * v.z + m.m41 * v.w,
				m.m12* v.x + m.m22 * v.y * m.m32 * v.z + m.m42 * v.w,
				m.m13* v.x + m.m23 * v.y * m.m33 * v.z + m.m43 * v.w,
				m.m14* v.x + m.m24 * v.y * m.m34 * v.z + m.m44 * v.w
		};
	}

	template<typename T>
	inline mat4<T> operator*(const T a, const mat4<T>& m) {
		return mat4<T>{
			m.m11* a, m.m21* a, m.m31* a, m.m41* a,
				m.m12* a, m.m22* a, m.m32* a, m.m42* a,
				m.m13* a, m.m23* a, m.m33* a, m.m43* a,
				m.m14* a, m.m24* a, m.m34* a, m.m44* a
		};
	}

	template<typename T>
	inline mat4<T> operator*(const mat4<T>& m, const T a) {
		return mat4<T>{
			m.m11* a, m.m21* a, m.m31* a, m.m41* a,
				m.m12* a, m.m22* a, m.m32* a, m.m42* a,
				m.m13* a, m.m23* a, m.m33* a, m.m43* a,
				m.m14* a, m.m24* a, m.m34* a, m.m44* a
		};
	}

	template<typename T>
	inline mat4<T> operator*(const mat4<T>& m, const mat4<T>& other) {
		mat4<T> temp;
		temp.m11 = m.m11 * other.m11 + m.m12 * other.m21 + m.m13 * other.m31 + m.m14 * other.m41;
		temp.m12 = m.m11 * other.m12 + m.m12 * other.m22 + m.m13 * other.m32 + m.m14 * other.m42;
		temp.m13 = m.m11 * other.m13 + m.m12 * other.m23 + m.m13 * other.m33 + m.m14 * other.m43;
		temp.m14 = m.m11 * other.m14 + m.m12 * other.m24 + m.m13 * other.m34 + m.m14 * other.m44;
		temp.m21 = m.m21 * other.m11 + m.m22 * other.m21 + m.m23 * other.m31 + m.m24 * other.m41;
		temp.m22 = m.m21 * other.m12 + m.m22 * other.m22 + m.m23 * other.m32 + m.m24 * other.m42;
		temp.m23 = m.m21 * other.m13 + m.m22 * other.m23 + m.m23 * other.m33 + m.m24 * other.m43;
		temp.m24 = m.m21 * other.m14 + m.m22 * other.m24 + m.m23 * other.m34 + m.m24 * other.m44;
		temp.m31 = m.m31 * other.m11 + m.m32 * other.m21 + m.m33 * other.m31 + m.m34 * other.m41;
		temp.m32 = m.m31 * other.m12 + m.m32 * other.m22 + m.m33 * other.m32 + m.m34 * other.m42;
		temp.m33 = m.m31 * other.m13 + m.m32 * other.m23 + m.m33 * other.m33 + m.m34 * other.m43;
		temp.m34 = m.m31 * other.m14 + m.m32 * other.m24 + m.m33 * other.m34 + m.m34 * other.m44;
		temp.m41 = m.m41 * other.m11 + m.m42 * other.m21 + m.m43 * other.m31 + m.m44 * other.m41;
		temp.m42 = m.m41 * other.m12 + m.m42 * other.m22 + m.m43 * other.m32 + m.m44 * other.m42;
		temp.m43 = m.m41 * other.m13 + m.m42 * other.m23 + m.m43 * other.m33 + m.m44 * other.m43;
		temp.m44 = m.m41 * other.m14 + m.m42 * other.m24 + m.m43 * other.m34 + m.m44 * other.m44;
		return temp;
	}

	template<typename T>
	inline mat4<T> operator/(const T a, const mat4<T>& m) {
		return mat4<T>{
			m.m11 / a, m.m21 / a, m.m31 / a, m.m41 / a,
				m.m12 / a, m.m22 / a, m.m32 / a, m.m42 / a,
				m.m13 / a, m.m23 / a, m.m33 / a, m.m43 / a,
				m.m14 / a, m.m24 / a, m.m34 / a, m.m44 / a
		};
	}

	template<typename T>
	inline mat4<T> operator/(const mat4<T>& m, const T a) {
		return mat4<T>{
			m.m11 / a, m.m21 / a, m.m31 / a, m.m41 / a,
				m.m12 / a, m.m22 / a, m.m32 / a, m.m42 / a,
				m.m13 / a, m.m23 / a, m.m33 / a, m.m43 / a,
				m.m14 / a, m.m24 / a, m.m34 / a, m.m44 / a
		};
	}

	template<typename T>
	inline mat4<T> operator~(const mat4<T>& m) {
		return mat4<T>{
			~m.m11, ~m.m21, ~m.m31, ~m.m41,
				~m.m12, ~m.m22m ~m.m32, ~m.m42,
				~m.m13, ~m.m23, ~m.m33, ~m.m43,
				~m.m14, ~m.m24, ~m.m34, ~m.m44
		};
	}

	template<typename T>
	inline mat4<T> operator-(const mat4<T>& m) {
		return mat4<T>{
			-m.m11, -m.m21, -m.m31, -m.m41,
				-m.m12, -m.m22m - m.m32, -m.m42,
				-m.m13, -m.m23, -m.m33, -m.m43,
				-m.m14, -m.m24, -m.m34, -m.m44
		};
	}

	template <typename T>
	inline const T* glPtr(const mat4<T>& m) {
		return reinterpret_cast<const T*>(&m);
	}
}