#pragma once

// -----
// Types
// -----

typedef void*   hwindow; // window handle

struct WindowInfo
{
    char*   title;
	u16     width;
    u16     height;
    u16     x;
    u16     y;
};

// Desired platform window allocation size.
// Use this to preallocate a block of memory
// that should be passed during window creation.
extern const u16 WINDOW_ALLOC_SIZE;

// ----
// Core
// ----

bool    window_init(hwindow win, WindowInfo* info);     // init window in preallocated memory
void    window_show(hwindow win);                       // display window
void    window_destroy(hwindow win);                    // destroy the window
void    window_update(hwindow win);                     // poll window events
void    window_close(hwindow win);                      // close the window
bool    window_active(hwindow win);                     // window not closed
void    window_size(hwindow win, u16* w, u16* h);       // window whole size
void    window_size_inner(hwindow win, u16* w, u16* h); // window inner renderable size
void*   window_native(hwindow win);                     // window native platform handle
bool    window_cursor_lock(hwindow win, bool lock);     // lock/unlock cursor within window
s32     window_cursor_show(hwindow win, bool show);     // show/hide cursor in window

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

inline void window_ortho_center(hwindow win, f32* ortho)
{
    u16 w, h;
    window_size_inner(win, &w, &h);
    ortho_center(w, h, ortho);
}

inline f32 window_aspect(hwindow win)
{
    u16 w, h;
    window_size_inner(win, &w, &h);
    return aspect(w, h);
}
