#include "pch.h"
#include "gdlmath.h"
#include <cmath>

namespace gdl
{
    s32 abs(s32 n)
    {
        const s32 sign = n >> 31;
        return (n ^ sign) - sign;
    }

    f32 absf(f32 n)
    {
        s32 tmp = *reinterpret_cast<s32*>(&n);
        tmp &= 0x7FFFFFFF; // clear sign bit
        return *reinterpret_cast<f32*>(&tmp);
    }

    f32 sqrt(f32 n)
    {
        return sqrtf(n);
    }

    f32 sqrt_inv(f32 n)
    {
        return 1 / sqrtf(n);
    }

    f32 rad(f32 d)
    {
        return d * (PI / 180.0f);
    }

    f32 deg(f32 r)
    {
        return r * (180.0f / PI);
    }

    f32 cos(f32 r)
    {
        return cosf(r);
    }

    f32 sin(f32 r)
    {
        return sinf(r);
    }

    f32 tan(f32 r)
    {
        return tanf(r);
    }
}
