#pragma once

#include "wb/core/types.h"

namespace wb {
	template<typename T>
	union vec2 {
		struct {
			T x, y;
		};
		struct {
			T r, g;
		};
		struct {
			T u, v;
		};
		struct {
			T s, t;
		};
		T data[2];
	};

	typedef vec2<i8> v2i8;
	typedef vec2<i16> v2i16;
	typedef vec2<i32> v2i32;
	typedef vec2<i64> v2i64;
	typedef vec2<f32> v2f32;
	typedef vec2<f64> v2f64;

	typedef vec2<u8> v2u8;
	typedef vec2<u16> v2u16;
	typedef vec2<u32> v2u32;
	typedef vec2<u64> v2u64;

	typedef vec2<f32> fvec2;
	typedef vec2<i32> ivec2;
	typedef vec2<real> rvec2;

	template<typename T>
	union vec3 {
		struct {
			T x, y, z;
		};
		struct {
			T r, g, b;
		};
		struct {
			T s, t, u;
		};
		T data[3];
	};

	typedef vec3<i8> v3i8;
	typedef vec3<i16> v3i16;
	typedef vec3<i32> v3i32;
	typedef vec3<i64> v3i64;
	typedef vec3<f32> v3f32;
	typedef vec3<f64> v3f64;

	typedef vec3<u8> v3u8;
	typedef vec3<u16> v3u16;
	typedef vec3<u32> v3u32;
	typedef vec3<u64> v3u64;

	typedef vec3<f32> fvec3;
	typedef vec3<i32> ivec3;
	typedef vec3<real> rvec3;

	template<typename T>
	union vec4 {
		struct {
			T x, y, z, w;
		};
		struct {
			T r, g, b, a;
		};
		struct {
			T s, t, u, v;
		};
		T data[4];
	};

	typedef vec4<i8> v4i8;
	typedef vec4<i16> v4i16;
	typedef vec4<i32> v4i32;
	typedef vec4<i64> v4i64;
	typedef vec4<f32> v4f32;
	typedef vec4<f64> v4f64;

	typedef vec4<u8> v4u8;
	typedef vec4<u16> v4u16;
	typedef vec4<u32> v4u32;
	typedef vec4<u64> v4u64;

	typedef vec4<f32> fvec4;
	typedef vec4<i32> ivec4;
	typedef vec4<real> rvec4;

#include "vector.inl"

}