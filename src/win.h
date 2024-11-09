#pragma once

// -----
// Types
// -----

typedef void*   winhandle; // window handle

struct WindowInfo
{
    char*   Title;
	u16     Width;
    u16     Height;
    u16     X;
    u16     Y;
};

// Desired platform window allocation size.
extern const u16 WIN_ALLOC_SIZE;

// ----
// Core
// ----

// To create a window, pointer to preallocated memory should be passed.
bool    wincreate(WindowInfo* info, winhandle win);
void    windestroy(winhandle win);
void    winupdate(winhandle win);
void    winclose(winhandle win);
bool    winactive(winhandle win);
void    winsize(winhandle win, u16* w, u16* h);

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

inline void winorthocenter(winhandle win, f32* ortho)
{
    u16 w, h;
    winsize(win, &w, &h);
    orthocenter(w, h, ortho);
}

inline f32 winaspect(winhandle win)
{
    u16 w, h;
    winsize(win, &w, &h);
    return aspect(w, h);
}
