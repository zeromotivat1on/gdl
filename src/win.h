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

extern const u16 WIN_ALLOC_SIZE;

// ----
// Core
// ----

// To create a window, pointer to preallocated memory should be passed.
// Desired window size can be obtained from appropriate function.

bool    wincreate(WindowInfo* info, winhandle win);
void    windestroy(winhandle win);
void    winupdate(winhandle win);
void    winclose(winhandle win);
bool    winclosed(winhandle win);
void    winsize(winhandle win, u16* w, u16* h);

// -----
// Extra
// -----

// Fill orthographic data at center of a given dimensions in order [left, right, bottom, top]
inline void winorthocenter(f32 w, f32 h, f32* ortho)
{
	const f32 whalf = w * 0.5f;
	const f32 hhalf = h * 0.5f;

    ortho[0] = -whalf;
    ortho[1] =  whalf;
    ortho[2] = -hhalf;
    ortho[3] =  hhalf;
}

// Get window aspect ratio.
inline f32 winaspect(f32 w, f32 h)
{
    return w / h;
}
