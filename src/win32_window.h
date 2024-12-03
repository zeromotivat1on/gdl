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
    HWND        hwnd;
    // DIC      device;
};
