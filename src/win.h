#pragma once

#include "input.h"

#ifdef WIN32
#include "win32_win.h"
#define PLATFORM_WINDOW Win32Window win32
#endif

// ---------
// Callbacks
// ---------

typedef void(*window_char_callback)(Window* win, u32 character);

// -----
// Types
// -----

enum Cursor_Flags : u8
{
    CURSOR_VISIBLE = BIT(0),
    CURSOR_LOCKED = BIT(1),
    CURSOR_CONSTRAINED = BIT(2),
};

struct Window_Info
{
    char*   title;
	u16     width;
    u16     height;
    u16     x;
    u16     y;
};

// TODO: hide the details from client to encourage usage of functions?
struct Window
{
    u8 cursor_flags;

    struct
    {
        window_char_callback character;
    } callbacks;
    
    bit128  keys;
    bit128  keys_last;
    bit128  keys_pressed;
    bit128  keys_released;

    u8      mouse_buttons;
    u8      mouse_buttons_last;
    u8      mouse_buttons_pressed;
    u8      mouse_buttons_released;
    
    s16     mouse_axes[MOUSE_AXIS_COUNT];
    
    PLATFORM_WINDOW;
};

// Desired window allocation size.
// Use this to preallocate a block of memory that should be passed during window init.
inline constexpr u16 WINDOW_ALLOC_SIZE = sizeof(Window);

// ----
// Core
// ----

bool    window_init(Window* win, Window_Info* info);    // init window in preallocated memory
void    window_show(Window* win);                       // display window
void    window_destroy(Window* win);                    // destroy the window
void    window_update(Window* win);                     // poll window events
void    window_close(Window* win);                      // close the window
bool    window_active(Window* win);                     // window not closed
void    window_size(Window* win, u16* w, u16* h);       // window whole size
void    window_size_inner(Window* win, u16* w, u16* h); // window inner renderable size
void*   window_native(Window* win);                     // window native platform handle

void    window_set_char_callback(Window* win, window_char_callback callback);

bool    window_cursor_lock(Window* win, bool lock);     // lock/unlock cursor within window
s32     window_cursor_show(Window* win, bool show);     // show/hide cursor in window
void    window_cursor_constrain(Window* win, bool constrain); // keep cursor within window
u8      window_cursor_flags(Window* win);
void    window_cursor_pos_absolute(Window* win, u16* x, u16* y);
void    window_cursor_pos_relative(Window* win, u16* x, u16* y);

// -----
// Extra
// -----

// Fill orthographic data at center of a given dimensions in order [left, right, bottom, top]
inline void ortho_center(f32 w, f32 h, f32* ortho)
{
	const f32 whalf = w * 0.5f;
	const f32 hhalf = h * 0.5f;

    ortho[0] = -whalf;
    ortho[1] =  whalf;
    ortho[2] = -hhalf;
    ortho[3] =  hhalf;
}

inline f32 aspect(f32 w, f32 h)
{
    return w / h;
}

inline void window_ortho_center(Window* win, f32* ortho)
{
    u16 w, h;
    window_size_inner(win, &w, &h);
    ortho_center(w, h, ortho);
}

inline f32 window_aspect(Window* win)
{
    u16 w, h;
    window_size_inner(win, &w, &h);
    return aspect(w, h);
}
