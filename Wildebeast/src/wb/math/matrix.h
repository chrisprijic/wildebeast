#pragma once

#include "wb/core/types.h"

namespace wb {
	//#define COLUMN_MAJOR -- define this if you want to use it.
#define ROW_MAJOR

	template<typename T>
	union mat2 {
		struct {
#ifdef COLUMN_MAJOR
			T m11, m21, m12, m22;
#else // ROW_MAJOR
			T m11, m12, m21, m22;
#endif
		};
		struct {
			vec2<T> c1, c2;
		};
		T data[4];
	};

	typedef mat2<i8> m2i8;
	typedef mat2<i16> m2i16;
	typedef mat2<i32> m2i32;
	typedef mat2<i64> m2i64;
	typedef mat2<f32> m2f32;
	typedef mat2<f64> m2f64;

	typedef mat2<u8> m2u8;
	typedef mat2<u16> m2u16;
	typedef mat2<u32> m2u32;
	typedef mat2<u64> m2u64;

	typedef mat2<f32> fmat2;
	typedef mat2<i32> imat2;
	typedef mat2<real> rmat2;

	template<typename T>
	union mat3 {
		struct {
#ifdef COLUMN_MAJOR
			T m11, m21, m31, m12, m22, m32, m13, m23, m33;
#else // ROW_MAJOR
			T m11, m12, m13, m21, m22, m23, m31, m32, m33;
#endif
		};
		struct {
			vec3<T> c1, c2, c3;
		};
		T data[9];
	};

	typedef mat3<i8> m3i8;
	typedef mat3<i16> m3i16;
	typedef mat3<i32> m3i32;
	typedef mat3<i64> m3i64;
	typedef mat3<f32> m3f32;
	typedef mat3<f64> m3f64;

	typedef mat3<u8> m3u8;
	typedef mat3<u16> m3u16;
	typedef mat3<u32> m3u32;
	typedef mat3<u64> m3u64;

	typedef mat3<f32> fmat3;
	typedef mat3<i32> imat3;
	typedef mat3<real> rmat3;

	template<typename T>
	union mat4 {
		struct {
#ifdef COLUMN_MAJOR
			T m11, m21, m31, m41, m12, m22, m32, m42, m13, m23, m33, m43, m14, m24, m34, m44;
#else // ROW_MAJOR
			T m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
#endif
		};
		struct {
			vec4<T> c1, c2, c3, c4;
		};
		T data[16];
	};

	typedef mat4<i8> m4i8;
	typedef mat4<i16> m4i16;
	typedef mat4<i32> m4i32;
	typedef mat4<i64> m4i64;
	typedef mat4<f32> m4f32;
	typedef mat4<f64> m4f64;

	typedef mat4<u8> m4u8;
	typedef mat4<u16> m4u16;
	typedef mat4<u32> m4u32;
	typedef mat4<u64> m4u64;

	typedef mat4<f32> fmat4;
	typedef mat4<i32> imat4;
	typedef mat4<real> rmat4;
}

#include "matrix.inl"