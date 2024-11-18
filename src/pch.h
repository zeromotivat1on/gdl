#pragma once

// ------------
// STD Includes
// ------------

#include <cstdint>
#include <cstring>
#include <stdarg.h>

// -----------------
// Platform Includes
// -----------------

#if defined(WIN32)
#include "Windows.h"
#endif

// ------------
// GDL Includes
// ------------

#include "msg.h"

// -----------------
// Fundamental types
// -----------------

using s8  = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = float;
using f64 = double;

// ------
// Macros
// ------

#define MACRO_EXPAND(x)         x
#define MACRO_STRING(x)         #x

#define MACRO_GLUE_(a, b)       a ## b
#define MACRO_GLUE(a, b)        MACRO_GLUE_(a, b)

#define STRUCT_ZERO(x)          x{0}

#define FPS(n)                  (1.0f / (n))
#define ARRAY_COUNT(arr)        (sizeof(arr) / sizeof(arr[0]))

#define BIT(x)                      (1ull << (x))
#define BIT_SET(val, pos)           ((val) |= (1ull << (pos)))
#define BIT_CLEAR(val, pos)         ((val) &= ~(1ull << (pos)))
// Set or clear bit based on test.
#define BIT_SORC(val, pos, test) ((val) = ((test) ? ((val) | (1ull << (pos))) : ((val) & ~(1ull << (pos)))))
#define BIT_TOGGLE(val, pos)        ((val) ^= (1ull << (pos)))
#define BIT_CHECK(val, pos)         (((val) & (1ull << (pos))) != 0)

#define INDEX_NONE              -1

// -----
// Error
// -----

#ifdef BUILD_RELEASE

#define DEBUG_BREAK()
#define ASSERT(x)
#define PANIC(x)

#else // ^^^ BUILD_RELEASE // vvv NOT_BUILD_RELEASE

#ifdef WIN32
#define DEBUG_BREAK() __debugbreak()
#endif // ^^^ WIN32

#define ASSERT(x)   if (!(x)) { do_assert(MACRO_STRING(x), __FILE__, __LINE__); }
#define PANIC(x)    if ((x)) { do_panic(MACRO_STRING(x), __FILE__, __LINE__); }

inline void do_assert(const char* cond, const char* filename, u32 line)
{
    msg_critical("Assert (%s) at (%s:%u)", cond, filename, line);
    DEBUG_BREAK();
}

inline void do_panic(const char* cond, const char* filename, u32 line)
{
    msg_critical("Panic (%s) at (%s:%u)", cond, filename, line);
    DEBUG_BREAK();
}
#endif // ^^^ NOT_BUILD_RELEASE
