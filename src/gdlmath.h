#pragma once

// ---------
// Constants
// ---------

inline constexpr f32 PI = 3.14159265358979323846f;

// ---------
// Functions
// ---------

template<typename T> T Sign(const T& n) { return (n > 0) - (n < 0); }
template<typename T> T Square(const T& n) { return n * n; }
template<typename T> T Cube(const T& n) { return n * n * n; }
template<typename T> T Clamp(const T& n, const T& min, const T& max) { return (n < min) ? min : (n > max ? max : n); }
template<typename T> T Swap(T& a, T& b) { T temp = a; a = b; b = temp; }

s32 Abs(s32 n);
f32 Absf(f32 n);
f32 Sqrt(f32 n);
f32 InvSqrt(f32 n);

f32 Rad(f32 d);
f32 Deg(f32 r);

f32 Cos(f32 r);
f32 Sin(f32 r);
f32 Tan(f32 r);
