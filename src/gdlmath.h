﻿#pragma once

// ---------
// Constants
// ---------

inline constexpr f32 PI = 3.14159265358979323846f;

// ---------
// Functions
// ---------

namespace gdl
{
	template<typename T> s32 sign(const T& n) { return (n > 0) - (n < 0); }
	template<typename T> T square(const T& n) { return n * n; }
	template<typename T> T cube(const T& n) { return n * n * n; }
	template<typename T> T clamp(const T& n, const T& min, const T& max) { return (n < min) ? min : (n > max ? max : n); }
	template<typename T> T swap(T& a, T& b) { T temp = a; a = b; b = temp; }

	s32 abs(s32 n);
	f32 absf(f32 n);
	f32 sqrt(f32 n);
	f32 sqrt_inv(f32 n);

	f32 rad(f32 d);
	f32 deg(f32 r);

	f32 cos(f32 r);
	f32 sin(f32 r);
	f32 tan(f32 r);
}
