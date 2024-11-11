#pragma once

// -----
// Types
// -----

typedef void*   whandle; // window handle

struct WindowInfo
{
    char*   Title;
	u16     Width;
    u16     Height;
    u16     X;
    u16     Y;
};

// Desired platform window allocation size.
extern const u16 WINDOW_ALLOC_SIZE;

// ----
// Core
// ----

bool    wcreate(WindowInfo* info, whandle win);     // create window in preallocated memory
void    wdestroy(whandle win);                      // destroy the window
void    wupdate(whandle win);                       // poll window events
void    wclose(whandle win);                        // close the window
bool    wactive(whandle win);                       // window not closed
void    wsize(whandle win, u16* w, u16* h);         // window whole size
void    wsizeinner(whandle win, u16* w, u16* h);    // window inner renderable size
void*   wnative(whandle win);                       // window native platform handle
bool    wcursor(whandle win, bool lock);            // lock/unlock cursor from window

// -----
// Extra
// -----

// Fill orthographic data at center of a given dimensions in order [left, right, bottom, top]
inline void orthocenter(f32 w, f32 h, f32* ortho)
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

inline void worthocenter(whandle win, f32* ortho)
{
    u16 w, h;
    wsize(win, &w, &h);
    orthocenter(w, h, ortho);
}

inline f32 waspect(whandle win)
{
    u16 w, h;
    wsize(win, &w, &h);
    return aspect(w, h);
}
