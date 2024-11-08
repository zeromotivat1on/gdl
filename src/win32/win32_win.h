#pragma once

#include "input.h"
#include "bit.h"

struct Win32Window
{
    // --------
    // Platform
    // --------

    wchar_t*    ClassName;
    ATOM        Class;
    HINSTANCE   Instance;
    HWND        Handle;
    // DIC         Device;

    // -----
    // Input
    // -----

    u128        Keys;
    u128        KeysLast;
    u128        KeysPressed;
    u128        KeysReleased;

    u8          MouseButtons;
    u8          MouseButtonsLast;
    u8          MouseButtonsPressed;
    u8          MouseButtonsReleased;
    
    f32         MouseAxes[MOUSE_AXIS_COUNT];
    
    s16         VirtualKeys[KEY_COUNT]; // key to virtual keycode
    s16         Scancodes[KEY_COUNT];   // key to keyboard scancode
    s16         Keycodes[512];          // virtual keycode to key
    char        Keynames[KEY_COUNT][4]; // key visual representation
};
