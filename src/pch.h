// ------------
// STD Includes
// ------------

#include <cstdint>
#include <cstring>

// -----------------
// Platform Includes
// -----------------

#if defined(PLATFORM_WIN32)
#include "Windows.h"
#endif

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

#define PANIC(x)                if ((x)) { *(int*)0 = 0; }
#define STRUCT_ZERO(x)          x{0}

#define FPS(n)                  (1.0f / (n))
#define ARRAY_COUNT(arr)        (sizeof(arr) / sizeof(arr[0]))

#define BIT(x)                  (1ull << (x))
#define BIT_SET(val, pos)       ((val) |= (1ull << (pos)))
#define BIT_CLEAR(val, pos)     ((val) &= ~(1ull << (pos)))
#define BIT_TOGGLE(val, pos)    ((val) ^= (1ull << (pos)))
#define BIT_CHECK(val, pos)     (((val) & (1ull << (pos))) != 0)

#define INDEX_NONE              -1

