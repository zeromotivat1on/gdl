#pragma once

#include "gdlmath.h"

struct mat3;

struct vec2
{
    f32             x;
    f32             y;

                    vec2();
    explicit        vec2(f32 a);
    explicit        vec2(f32 a, f32 b);

    f32			    operator[](s32 index) const;
    f32&			operator[](s32 index);
    vec2			operator-() const;
    vec2			operator+(const vec2& a) const;
    vec2			operator-(const vec2& a) const;
    f32			    operator*(const vec2& a) const;
    vec2			operator*(f32 a) const;
    vec2			operator/(f32 a) const;
    vec2&		    operator+=(const vec2& a);
    vec2&		    operator-=(const vec2& a);
    vec2&		    operator/=(const vec2& a);
    vec2&		    operator/=(f32 a);
    vec2&		    operator*=(f32 a);

    bool			operator==(const vec2& a) const;
    bool			operator!=(const vec2& a) const;

    friend vec2	    operator*(f32 a, vec2 b);

    vec2& 			set(f32 a, f32 b);
    vec2&			zero();

    bool			equal(const vec2& a) const;
    bool			equal(const vec2& a, f32 epsilon) const;

    f32			    length() const;
    f32			    length_sqr() const;
    f32             dot(const vec2& a) const;
    vec2&           normalize();            // normalize vector
    vec2&		    truncate(f32 length);   // cap vector length

    s32				dimension() const;

    f32*			ptr();
    const f32*	    ptr() const;

    vec2&			clamp(const vec2& min, const vec2& max);
    vec2&			snap(); // snap to closest integer value
    vec2&			lerp(const vec2& v1, const vec2& v2, f32 alpha);
};

inline vec2::vec2()
    : x(0.0f), y(0.0f)
{
}

inline vec2::vec2(f32 a)
    : x(a), y(a)
{
}

inline vec2::vec2(f32 a, f32 b)
    : x(a), y(b)
{
}

inline f32 vec2::operator[](s32 index) const
{
    return (&x)[index];
}

inline f32& vec2::operator[](s32 index)
{
    return (&x)[index];
}

inline vec2 vec2::operator-() const
{
    return vec2(-x, -y);
}

inline vec2 vec2::operator+(const vec2& a) const
{
    return vec2(x + a.x, y + a.y);
}

inline vec2 vec2::operator-(const vec2& a) const
{
    return vec2(x - a.x, y - a.y);
}

inline f32 vec2::operator*(const vec2& a) const
{
    return dot(a);
}

inline vec2 vec2::operator*(f32 a) const
{
    return vec2(x * a, y * a);
}

inline vec2 vec2::operator/(f32 a) const
{
    const f32 inv = 1.0f / a;
    return vec2(x * inv, y * inv);
}

inline vec2& vec2::operator+=(const vec2& a)
{
    x += a.x;
    y += a.y;
    return *this;
}

inline vec2& vec2::operator-=(const vec2& a)
{
    x -= a.x;
    y -= a.y;
    return *this;
}

inline vec2& vec2::operator/=(const vec2& a)
{
    x /= a.x;
    y /= a.y;
    return *this;
}

inline vec2& vec2::operator/=(f32 a)
{
    const f32 inv = 1.0f / a;
    x *= inv;
    y *= inv;
    return *this;
}

inline vec2& vec2::operator*=(f32 a)
{
    x *= a;
    y *= a;
    return *this;
}

inline bool vec2::operator==(const vec2& a) const
{
    return equal(a);
}

inline bool vec2::operator!=(const vec2& a) const
{
    return !(*this == a);
}

inline vec2 operator*(f32 a, vec2 b)
{
    return vec2(b.x * a, b.y * a);
}

inline vec2& vec2::set(f32 a, f32 b)
{
    x = a;
    y = b;
    return *this;
}

inline vec2& vec2::zero()
{
    x = y = 0.0f;
    return *this;
}

inline bool vec2::equal(const vec2& a) const
{
    return x == a.x && y == a.y;
}

inline bool vec2::equal(const vec2& a, f32 epsilon) const
{
    return gdl::absf(x - a.x) <= epsilon &&
           gdl::absf(y - a.y) <= epsilon;
}

inline f32 vec2::length() const
{
    return gdl::sqrt(x * x + y * y);
}

inline f32 vec2::length_sqr() const
{
    return x * x + y * y;
}

inline f32 vec2::dot(const vec2& a) const
{
    return x * a.x + y * a.y;
}

inline vec2& vec2::normalize()
{
    const f32 length_inv = gdl::sqrt_inv(x * x + y * y);

    x *= length_inv;
    y *= length_inv;

    return *this;
}

inline vec2& vec2::truncate(f32 length)
{
    if (length == 0.0f)
    {
        zero();
        return *this;
    }

    const f32 length_square = x * x + y * y;
    if (length_square > length * length)
    {
        const f32 scale_factor = length * gdl::sqrt_inv(length_square);
        x *= scale_factor;
        y *= scale_factor;
    }

    return *this;
}

inline s32 vec2::dimension() const
{
    return 2;
}

inline f32* vec2::ptr()
{
    return &x;
}

inline const f32* vec2::ptr() const
{
    return &x;
}

inline vec2& vec2::clamp(const vec2& min, const vec2& max)
{
    x = gdl::clamp(x, min.x, max.x);
    y = gdl::clamp(y, min.y, max.y);
    return *this;
}

inline vec2& vec2::snap()
{
    x = (f32)((s32)x);
    y = (f32)((s32)y);
    return *this;
}

inline vec2& vec2::lerp(const vec2& v1, const vec2& v2, f32 alpha)
{
    if (alpha <= 0.0f)
    {
        *this = v1;
    }
    else if (alpha >= 1.0f)
    {
        *this = v2;
    }
    else
    {
        *this = v1 + alpha * (v2 - v1);
    }

    return *this;
}

struct vec3
{
    f32             x;
    f32             y;
    f32             z;

                    vec3();
    explicit        vec3(f32 a);
    explicit        vec3(f32 a, f32 b, f32 c);

    f32			    operator[](s32 index) const;
    f32&			operator[](s32 index);
    vec3			operator-() const;
    vec3			operator+(const vec3& a) const;
    vec3			operator-(const vec3& a) const;
    f32			    operator*(const vec3& a) const;
    vec3			operator*(f32 a) const;
    vec3			operator/(f32 a) const;
    vec3&		    operator+=(const vec3& a);
    vec3&		    operator-=(const vec3& a);
    vec3&		    operator/=(const vec3& a);
    vec3&		    operator/=(f32 a);
    vec3&		    operator*=(f32 a);

    bool			operator==(const vec3& a) const;
    bool			operator!=(const vec3& a) const;

    friend vec3	    operator*(f32 a, vec3 b);

    vec3& 			set(f32 a, f32 b, f32 c);
    vec3&			zero();

    bool			equal(const vec3& a) const;
    bool			equal(const vec3& a, f32 epsilon) const;

    f32			    length() const;
    f32			    length_sqr() const;
    f32             dot(const vec3& a) const;
    vec3            cross(const vec3& a) const;
    vec3&           normalize();            // normalize vector
    vec3&		    truncate(f32 length);   // cap vector length

    s32				dimension() const;

    f32			    yaw() const;
    f32			    pitch() const;
    const vec2&	    to_vec2() const;
    vec2&		    to_vec2();

    f32*			ptr();
    const f32*	    ptr() const;

    vec3&			clamp(const vec3& min, const vec3& max);
    vec3&			snap(); // snap to closest integer value
    vec3&			lerp(const vec3& v1, const vec3& v2, f32 alpha);
};

inline vec3::vec3()
    : x(0.0f), y(0.0f), z(0.0f)
{
}

inline vec3::vec3(f32 a)
    : x(a), y(a), z(a)
{
}

inline vec3::vec3(f32 a, f32 b, f32 c)
    : x(a), y(b), z(c)
{
}

inline f32 vec3::operator[](s32 index) const
{
    return (&x)[index];
}

inline f32& vec3::operator[](s32 index)
{
    return (&x)[index];
}

inline vec3 vec3::operator-() const
{
    return vec3(-x, -y, -z);
}

inline vec3 vec3::operator+(const vec3& a) const
{
    return vec3(x + a.x, y + a.y, z + a.z);
}

inline vec3 vec3::operator-(const vec3& a) const
{
    return vec3(x - a.x, y - a.y, z - a.z);
}

inline f32 vec3::operator*(const vec3& a) const
{
    return dot(a);
}

inline vec3 vec3::operator*(f32 a) const
{
    return vec3(x * a, y * a, z * a);
}

inline vec3 vec3::operator/(f32 a) const
{
    const f32 inv = 1.0f / a;
    return vec3(x * inv, y * inv, z * inv);
}

inline vec3& vec3::operator+=(const vec3& a)
{
    x += a.x;
    y += a.y;
    z += a.z;
    return *this;
}

inline vec3& vec3::operator-=(const vec3& a)
{
    x -= a.x;
    y -= a.y;
    z -= a.z;
    return *this;
}

inline vec3& vec3::operator/=(const vec3& a)
{
    x /= a.x;
    y /= a.y;
    z /= a.z;
    return *this;
}

inline vec3& vec3::operator/=(f32 a)
{
    const f32 inv = 1.0f / a;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

inline vec3& vec3::operator*=(f32 a)
{
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

inline bool vec3::operator==(const vec3& a) const
{
    return equal(a);
}

inline bool vec3::operator!=(const vec3& a) const
{
    return !(*this == a);
}

inline vec3 operator*(f32 a, vec3 b)
{
    return vec3(b.x * a, b.y * a, b.z * a);
}

inline vec3& vec3::set(f32 a, f32 b, f32 c)
{
    x = a;
    y = b;
    z = c;
    return *this;
}

inline vec3& vec3::zero()
{
    x = y = z = 0.0f;
    return *this;
}

inline bool vec3::equal(const vec3& a) const
{
    return (x == a.x) && (y == a.y) && (z == a.z);
}

inline bool vec3::equal(const vec3& a, f32 epsilon) const
{
    return gdl::absf(x - a.x) <= epsilon &&
           gdl::absf(y - a.y) <= epsilon &&
           gdl::absf(z - a.z) <= epsilon;
}

inline f32 vec3::length() const
{
    return gdl::sqrt(x * x + y * y + z * z);
}

inline f32 vec3::length_sqr() const
{
    return x * x + y * y + z * z;
}

inline f32 vec3::dot(const vec3& a) const
{
    return x * a.x + y * a.y + z * a.z;
}

inline vec3 vec3::cross(const vec3& a) const
{
    return vec3(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
}

inline vec3& vec3::normalize()
{
    const f32 length_inv = gdl::sqrt_inv(x * x + y * y + z * z);

    x *= length_inv;
    y *= length_inv;
    z *= length_inv;

    return *this;
}

inline vec3& vec3::truncate(f32 length)
{
    if (length == 0.0f)
    {
        zero();
        return *this;
    }

    const f32 length_square = x * x + y * y + z * z;
    if (length_square > length * length)
    {
        const f32 scale_factor = length * gdl::sqrt_inv(length_square);
        x *= scale_factor;
        y *= scale_factor;
        z *= scale_factor;
    }

    return *this;
}

inline s32 vec3::dimension() const
{
    return 3;
}

inline f32 vec3::yaw() const
{
}

inline f32 vec3::pitch() const
{
}

inline const vec2& vec3::to_vec2() const
{
    return *(const vec2*)this;
}

inline vec2& vec3::to_vec2()
{
    return *(vec2*)this;
}

inline f32* vec3::ptr()
{
    return &x;
}

inline const f32* vec3::ptr() const
{
    return &x;
}

inline vec3& vec3::clamp(const vec3& min, const vec3& max)
{
    x = gdl::clamp(x, min.x, max.x);
    y = gdl::clamp(y, min.y, max.y);
    z = gdl::clamp(z, min.z, max.z);
    return *this;
}

inline vec3& vec3::snap()
{
    x = (f32)((s32)x);
    y = (f32)((s32)y);
    z = (f32)((s32)z);
    return *this;
}

inline vec3& vec3::lerp(const vec3& v1, const vec3& v2, f32 alpha)
{
    if (alpha <= 0.0f)
    {
        *this = v1;
    }
    else if (alpha >= 1.0f)
    {
        *this = v2;
    }
    else
    {
        *this = v1 + alpha * (v2 - v1);
    }

    return *this;
}

struct vec4
{
    f32             x;
    f32             y;
    f32             z;
    f32             w;

                    vec4();
    explicit        vec4(f32 a);
    explicit        vec4(f32 a, f32 b, f32 c, f32 d);

    f32			    operator[](s32 index) const;
    f32&			operator[](s32 index);
    vec4			operator-() const;
    vec4			operator+(const vec4& a) const;
    vec4			operator-(const vec4& a) const;
    f32			    operator*(const vec4& a) const;
    vec4			operator*(f32 a) const;
    vec4			operator/(f32 a) const;
    vec4&		    operator+=(const vec4& a);
    vec4&		    operator-=(const vec4& a);
    vec4&		    operator/=(const vec4& a);
    vec4&		    operator/=(f32 a);
    vec4&		    operator*=(f32 a);

    bool			operator==(const vec4& a) const;
    bool			operator!=(const vec4& a) const;

    friend vec4	    operator*(f32 a, vec4 b);

    vec4& 			set(f32 a, f32 b, f32 c, f32 d);
    vec4&			zero();

    bool			equal(const vec4& a) const;
    bool			equal(const vec4& a, f32 epsilon) const;

    f32			    length() const;
    f32			    length_sqr() const;
    f32             dot(const vec4& a) const;
    vec4&           normalize();            // normalize vector

    s32				dimension() const;

    const vec2&	    to_vec2() const;
    vec2&		    to_vec2();
    const vec3&	    to_vec3() const;
    vec3&		    to_vec3();

    f32*			ptr();
    const f32*	    ptr() const;

    vec4&			lerp(const vec4& v1, const vec4& v2, f32 alpha);
};

inline vec4::vec4()
    : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

inline vec4::vec4(f32 a)
    : x(a), y(a), z(a), w(a)
{

}

inline vec4::vec4(f32 a, f32 b, f32 c, f32 d)
    : x(a), y(b), z(c), w(d)
{
}

inline f32 vec4::operator[](s32 index) const
{
    return (&x)[index];
}

inline f32& vec4::operator[](s32 index)
{
    return (&x)[index];
}

inline vec4 vec4::operator-() const
{
    return vec4(-x, -y, -z, -w);
}

inline vec4 vec4::operator+(const vec4& a) const
{
    return vec4(x + a.x, y + a.y, z + a.z, w + a.w);
}

inline vec4 vec4::operator-(const vec4& a) const
{
    return vec4(x - a.x, y - a.y, z - a.z, w - a.w);
}

inline f32 vec4::operator*(const vec4& a) const
{
    return dot(a);
}

inline vec4 vec4::operator*(f32 a) const
{
    return vec4(x * a, y * a, z * a, w * a);
}

inline vec4 vec4::operator/(f32 a) const
{
    const f32 inv = 1.0f / a;
    return vec4(x * inv, y * inv, z * inv, w * inv);
}

inline vec4& vec4::operator+=(const vec4& a)
{
    x += a.x;
    y += a.y;
    z += a.z;
    w += a.w;
    return *this;
}

inline vec4& vec4::operator-=(const vec4& a)
{
    x -= a.x;
    y -= a.y;
    z -= a.z;
    w -= a.w;
    return *this;
}

inline vec4& vec4::operator/=(const vec4& a)
{
    x /= a.x;
    y /= a.y;
    z /= a.z;
    w /= a.w;
    return *this;
}

inline vec4& vec4::operator/=(f32 a)
{
    const f32 inv = 1.0f / a;
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
    return *this;
}

inline vec4& vec4::operator*=(f32 a)
{
    x *= a;
    y *= a;
    z *= a;
    w *= a;
    return *this;
}

inline bool vec4::operator==(const vec4& a) const
{
    return equal(a);
}

inline bool vec4::operator!=(const vec4& a) const
{
    return !(*this == a);
}

inline vec4 operator*(f32 a, vec4 b)
{
    return vec4(b.x * a, b.y * a, b.z * a, b.w * a);
}

inline vec4& vec4::set(f32 a, f32 b, f32 c, f32 d)
{
    x = a;
    y = b;
    z = c;
    w = d;
    return *this;
}

inline vec4& vec4::zero()
{
    x = y = z = w = 0.0f;
    return *this;
}

inline bool vec4::equal(const vec4& a) const
{
    return (x == a.x) && (y == a.y) && (z == a.z) && (w == a.w);
}

inline bool vec4::equal(const vec4& a, f32 epsilon) const
{
    return gdl::absf(x - a.x) <= epsilon &&
           gdl::absf(y - a.y) <= epsilon &&
           gdl::absf(z - a.z) <= epsilon &&
           gdl::absf(w - a.w) <= epsilon;
}

inline f32 vec4::length() const
{
    return gdl::sqrt(x * x + y * y + z * z + w * w);
}

inline f32 vec4::length_sqr() const
{
    return x * x + y * y + z * z + w * w;
}

inline f32 vec4::dot(const vec4& a) const
{
    return x * a.x + y * a.y + z * a.z + w * a.w;
}

inline vec4& vec4::normalize()
{
    const f32 lengthInv = gdl::sqrt_inv(x * x + y * y + z * z + w * w);

    x *= lengthInv;
    y *= lengthInv;
    z *= lengthInv;
    w *= lengthInv;

    return *this;
}

inline s32 vec4::dimension() const
{
    return 4;
}

inline const vec2& vec4::to_vec2() const
{
    return *(const vec2*)this;
}

inline vec2& vec4::to_vec2()
{
    return *(vec2*)this;
}

inline const vec3& vec4::to_vec3() const
{
    return *(const vec3*)this;
}

inline vec3& vec4::to_vec3()
{
    return *(vec3*)this;
}

inline f32* vec4::ptr()
{
    return &x;
}

inline const f32* vec4::ptr() const
{
    return &x;
}

inline vec4& vec4::lerp(const vec4& v1, const vec4& v2, f32 alpha)
{
    if (alpha <= 0.0f)
    {
        *this = v1;
    }
    else if (alpha >= 1.0f)
    {
        *this = v2;
    }
    else
    {
        *this = v1 + alpha * (v2 - v1);
    }

    return *this;
}

// -----
// Extra
// -----

inline vec3 vec3_forward(const vec3& start, const vec3& end)
{
    return (start - end).normalize();
}

inline vec3 vec3_right(const vec3& start, const vec3& end, const vec3& up)
{
    return (start - end).cross(up).normalize();
}

// Convert spherical coordinates (yaw, pitch) to cartesian coordinates (forward vector).
inline vec3 vec3_forward(f32 yaw, f32 pitch)
{
    const f32 ycos = gdl::cos(gdl::rad(yaw));
    const f32 ysin = gdl::sin(gdl::rad(yaw));
    const f32 pcos = gdl::cos(gdl::rad(pitch));
    const f32 psin = gdl::sin(gdl::rad(pitch));
    return vec3(ycos * pcos, psin, ysin * pcos).normalize();
}
