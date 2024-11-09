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

    vec2& 			Set(f32 a, f32 b);
    vec2&			Zero();

    bool			Equal(const vec2& a) const;
    bool			Equal(const vec2& a, f32 epsilon) const;

    f32			    Length() const;
    f32			    LengthSqr() const;
    f32             Dot(const vec2& a) const;
    vec2&           Normalize();            // normalize vector
    vec2&		    Truncate(f32 length);   // cap vector length

    s32				Dimension() const;

    f32*			Ptr();
    const f32*	    Ptr() const;

    vec2&			Clamp(const vec2& min, const vec2& max);
    vec2&			Snap(); // snap to closest integer value
    vec2&			Lerp(const vec2& v1, const vec2& v2, f32 alpha);
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
    return Dot(a);
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
    return Equal(a);
}

inline bool vec2::operator!=(const vec2& a) const
{
    return !(*this == a);
}

inline vec2 operator*(f32 a, vec2 b)
{
    return vec2(b.x * a, b.y * a);
}

inline vec2& vec2::Set(f32 a, f32 b)
{
    x = a;
    y = b;
    return *this;
}

inline vec2& vec2::Zero()
{
    x = y = 0.0f;
    return *this;
}

inline bool vec2::Equal(const vec2& a) const
{
    return x == a.x && y == a.y;
}

inline bool vec2::Equal(const vec2& a, f32 epsilon) const
{
    return Absf(x - a.x) <= epsilon &&
           Absf(y - a.y) <= epsilon;
}

inline f32 vec2::Length() const
{
    return Sqrt(x * x + y * y);
}

inline f32 vec2::LengthSqr() const
{
    return x * x + y * y;
}

inline f32 vec2::Dot(const vec2& a) const
{
    return x * a.x + y * a.y;
}

inline vec2& vec2::Normalize()
{
    const f32 lengthInv = InvSqrt(x * x + y * y);

    x *= lengthInv;
    y *= lengthInv;

    return *this;
}

inline vec2& vec2::Truncate(f32 length)
{
    if (length == 0.0f)
    {
        Zero();
        return *this;
    }

    const f32 lengthSquare = x * x + y * y;
    if (lengthSquare > length * length)
    {
        const f32 scaleFactor = length * InvSqrt(lengthSquare);
        x *= scaleFactor;
        y *= scaleFactor;
    }

    return *this;
}

inline s32 vec2::Dimension() const
{
    return 2;
}

inline f32* vec2::Ptr()
{
    return &x;
}

inline const f32* vec2::Ptr() const
{
    return &x;
}

inline vec2& vec2::Clamp(const vec2& min, const vec2& max)
{
    x = ::Clamp(x, min.x, max.x);
    y = ::Clamp(y, min.y, max.y);
    return *this;
}

inline vec2& vec2::Snap()
{
    x = (f32)((s32)x);
    y = (f32)((s32)y);
    return *this;
}

inline vec2& vec2::Lerp(const vec2& v1, const vec2& v2, f32 alpha)
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

    vec3& 			Set(f32 a, f32 b, f32 c);
    vec3&			Zero();

    bool			Equal(const vec3& a) const;
    bool			Equal(const vec3& a, f32 epsilon) const;

    f32			    Length() const;
    f32			    LengthSqr() const;
    f32             Dot(const vec3& a) const;
    vec3            Cross(const vec3& a) const;
    vec3&           Normalize();            // normalize vector
    vec3&		    Truncate(f32 length);   // cap vector length

    s32				Dimension() const;

    f32			    Yaw() const;
    f32			    Pitch() const;
    const vec2&	    Vec2() const;
    vec2&		    Vec2();

    f32*			Ptr();
    const f32*	    Ptr() const;

    vec3&			Clamp(const vec3& min, const vec3& max);
    vec3&			Snap();                 // snap to closest integer value
    vec3&			Lerp(const vec3& v1, const vec3& v2, f32 alpha);
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
    return Dot(a);
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
    return Equal(a);
}

inline bool vec3::operator!=(const vec3& a) const
{
    return !(*this == a);
}

inline vec3 operator*(f32 a, vec3 b)
{
    return vec3(b.x * a, b.y * a, b.z * a);
}

inline vec3& vec3::Set(f32 a, f32 b, f32 c)
{
    x = a;
    y = b;
    z = c;
    return *this;
}

inline vec3& vec3::Zero()
{
    x = y = z = 0.0f;
    return *this;
}

inline bool vec3::Equal(const vec3& a) const
{
    return (x == a.x) && (y == a.y) && (z == a.z);
}

inline bool vec3::Equal(const vec3& a, f32 epsilon) const
{
    return Absf(x - a.x) <= epsilon &&
           Absf(y - a.y) <= epsilon &&
           Absf(z - a.z) <= epsilon;
}

inline f32 vec3::Length() const
{
    return Sqrt(x * x + y * y + z * z);
}

inline f32 vec3::LengthSqr() const
{
    return x * x + y * y + z * z;
}

inline f32 vec3::Dot(const vec3& a) const
{
    return x * a.x + y * a.y + z * a.z;
}

inline vec3 vec3::Cross(const vec3& a) const
{
    return vec3(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
}

inline vec3& vec3::Normalize()
{
    const f32 lengthInv = InvSqrt(x * x + y * y + z * z);

    x *= lengthInv;
    y *= lengthInv;
    z *= lengthInv;

    return *this;
}

inline vec3& vec3::Truncate(f32 length)
{
    if (length == 0.0f)
    {
        Zero();
        return *this;
    }

    const f32 lengthSquare = x * x + y * y + z * z;
    if (lengthSquare > length * length)
    {
        const f32 scaleFactor = length * InvSqrt(lengthSquare);
        x *= scaleFactor;
        y *= scaleFactor;
        z *= scaleFactor;
    }

    return *this;
}

inline s32 vec3::Dimension() const
{
    return 3;
}

inline f32 vec3::Yaw() const
{
}

inline f32 vec3::Pitch() const
{
}

inline const vec2& vec3::Vec2() const
{
    return *(const vec2*)this;
}

inline vec2& vec3::Vec2()
{
    return *(vec2*)this;
}

inline f32* vec3::Ptr()
{
    return &x;
}

inline const f32* vec3::Ptr() const
{
    return &x;
}

inline vec3& vec3::Clamp(const vec3& min, const vec3& max)
{
    x = ::Clamp(x, min.x, max.x);
    y = ::Clamp(y, min.y, max.y);
    z = ::Clamp(z, min.z, max.z);
    return *this;
}

inline vec3& vec3::Snap()
{
    x = (f32)((s32)x);
    y = (f32)((s32)y);
    z = (f32)((s32)z);
    return *this;
}

inline vec3& vec3::Lerp(const vec3& v1, const vec3& v2, f32 alpha)
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

    vec4& 			Set(f32 a, f32 b, f32 c, f32 d);
    vec4&			Zero();

    bool			Equal(const vec4& a) const;
    bool			Equal(const vec4& a, f32 epsilon) const;

    f32			    Length() const;
    f32			    LengthSqr() const;
    f32             Dot(const vec4& a) const;
    vec4&           Normalize();            // normalize vector

    s32				Dimension() const;

    const vec2&	    Vec2() const;
    vec2&		    Vec2();
    const vec3&	    Vec3() const;
    vec3&		    Vec3();

    f32*			Ptr();
    const f32*	    Ptr() const;

    vec4&			Lerp(const vec4& v1, const vec4& v2, f32 alpha);
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
    return Dot(a);
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
    return Equal(a);
}

inline bool vec4::operator!=(const vec4& a) const
{
    return !(*this == a);
}

inline vec4 operator*(f32 a, vec4 b)
{
    return vec4(b.x * a, b.y * a, b.z * a, b.w * a);
}

inline vec4& vec4::Set(f32 a, f32 b, f32 c, f32 d)
{
    x = a;
    y = b;
    z = c;
    w = d;
    return *this;
}

inline vec4& vec4::Zero()
{
    x = y = z = w = 0.0f;
    return *this;
}

inline bool vec4::Equal(const vec4& a) const
{
    return (x == a.x) && (y == a.y) && (z == a.z) && (w == a.w);
}

inline bool vec4::Equal(const vec4& a, f32 epsilon) const
{
    return Absf(x - a.x) <= epsilon &&
           Absf(y - a.y) <= epsilon &&
           Absf(z - a.z) <= epsilon &&
           Absf(w - a.w) <= epsilon;
}

inline f32 vec4::Length() const
{
    return Sqrt(x * x + y * y + z * z + w * w);
}

inline f32 vec4::LengthSqr() const
{
    return x * x + y * y + z * z + w * w;
}

inline f32 vec4::Dot(const vec4& a) const
{
    return x * a.x + y * a.y + z * a.z + w * a.w;
}

inline vec4& vec4::Normalize()
{
    const f32 lengthInv = InvSqrt(x * x + y * y + z * z + w * w);

    x *= lengthInv;
    y *= lengthInv;
    z *= lengthInv;
    w *= lengthInv;

    return *this;
}

inline s32 vec4::Dimension() const
{
    return 4;
}

inline const vec2& vec4::Vec2() const
{
    return *(const vec2*)this;
}

inline vec2& vec4::Vec2()
{
    return *(vec2*)this;
}

inline const vec3& vec4::Vec3() const
{
    return *(const vec3*)this;
}

inline vec3& vec4::Vec3()
{
    return *(vec3*)this;
}

inline f32* vec4::Ptr()
{
    return &x;
}

inline const f32* vec4::Ptr() const
{
    return &x;
}

inline vec4& vec4::Lerp(const vec4& v1, const vec4& v2, f32 alpha)
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
