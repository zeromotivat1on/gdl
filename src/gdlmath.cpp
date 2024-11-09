#include "pch.h"
#include "gdlmath.h"
#include <cmath>

s32 Abs(s32 n)
{
    const s32 sign = n >> 31;
    return (n ^ sign) - sign;
}

f32 Absf(f32 n)
{
    s32 tmp = *reinterpret_cast<s32*>(&n);
    tmp &= 0x7FFFFFFF; // clear sign bit
    return *reinterpret_cast<f32*>(&tmp);
}

f32 Sqrt(f32 n)
{
    return sqrtf(n);
}

f32 InvSqrt(f32 n)
{
    return 1 / sqrtf(n);
}

f32 Rad(f32 d)
{
    return d * (PI / 180.0f);
}

f32 Deg(f32 r)
{
    return r * (180.0f / PI);
}

f32 Cos(f32 r)
{
    return cosf(r);
}

f32 Sin(f32 r)
{
    return sinf(r);
}

f32 Tan(f32 r)
{
    return tanf(r);
}
