#pragma once

#include "input.h"
#include "bit.h"

struct Win32Window
{
    // --------
    // Platform
    // --------

    wchar_t*    class_name;
    ATOM        class_atom;
    HINSTANCE   hinstance;
    HWND        handle;
    // DIC      device;

    // -----
    // Input
    // -----

    bit128      keys;
    bit128      keys_last;
    bit128      keys_pressed;
    bit128      keys_released;

    u8          mouse_buttons;
    u8          mouse_buttons_last;
    u8          mouse_buttons_pressed;
    u8          mouse_buttons_released;
    
    s16         mouse_axes[MOUSE_AXIS_COUNT];

    bool        cursor_constrained;
};
