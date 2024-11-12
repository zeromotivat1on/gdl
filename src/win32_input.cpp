#include "pch.h"
#include "str.h"
#include "input.h"
#include "win32_win.h"

void window_key_tables_init(void* win)
{
    Win32Window* win32 = (Win32Window*)win;

    memset(win32->VirtualKeys, KEY_INVALID, sizeof(win32->VirtualKeys));
    memset(win32->Scancodes, KEY_INVALID, sizeof(win32->Scancodes));
    memset(win32->Keycodes, KEY_INVALID, sizeof(win32->Keycodes));
    memset(win32->Keynames, 0, sizeof(win32->Keynames));

    win32->VirtualKeys[KEY_SPACE]         = VK_SPACE;
    win32->VirtualKeys[KEY_APOSTROPHE]    = VK_OEM_7;
    win32->VirtualKeys[KEY_COMMA]         = VK_OEM_COMMA;
    win32->VirtualKeys[KEY_MINUS]         = VK_OEM_MINUS;
    win32->VirtualKeys[KEY_PERIOD]        = VK_OEM_PERIOD;
    win32->VirtualKeys[KEY_SLASH]         = VK_OEM_2;
    win32->VirtualKeys[KEY_0]             = 0x30;
    win32->VirtualKeys[KEY_1]             = 0x31;
    win32->VirtualKeys[KEY_2]             = 0x32;
    win32->VirtualKeys[KEY_3]             = 0x33;
    win32->VirtualKeys[KEY_4]             = 0x34;
    win32->VirtualKeys[KEY_5]             = 0x35;
    win32->VirtualKeys[KEY_6]             = 0x36;
    win32->VirtualKeys[KEY_7]             = 0x37;
    win32->VirtualKeys[KEY_8]             = 0x38;
    win32->VirtualKeys[KEY_9]             = 0x39;
    win32->VirtualKeys[KEY_SEMICOLON]     = VK_OEM_1;
    win32->VirtualKeys[KEY_EQUAL]         = VK_OEM_PLUS;
    win32->VirtualKeys[KEY_A]             = 0x41;
    win32->VirtualKeys[KEY_B]             = 0x42;
    win32->VirtualKeys[KEY_C]             = 0x43;
    win32->VirtualKeys[KEY_D]             = 0x44;
    win32->VirtualKeys[KEY_E]             = 0x45;
    win32->VirtualKeys[KEY_F]             = 0x46;
    win32->VirtualKeys[KEY_G]             = 0x47;
    win32->VirtualKeys[KEY_H]             = 0x48;
    win32->VirtualKeys[KEY_I]             = 0x49;
    win32->VirtualKeys[KEY_J]             = 0x4A;
    win32->VirtualKeys[KEY_K]             = 0x4B;
    win32->VirtualKeys[KEY_L]             = 0x4C;
    win32->VirtualKeys[KEY_M]             = 0x4D;
    win32->VirtualKeys[KEY_N]             = 0x4E;
    win32->VirtualKeys[KEY_O]             = 0x4F;
    win32->VirtualKeys[KEY_P]             = 0x50;
    win32->VirtualKeys[KEY_Q]             = 0x51;
    win32->VirtualKeys[KEY_R]             = 0x52;
    win32->VirtualKeys[KEY_S]             = 0x53;
    win32->VirtualKeys[KEY_T]             = 0x54;
    win32->VirtualKeys[KEY_U]             = 0x55;
    win32->VirtualKeys[KEY_V]             = 0x56;
    win32->VirtualKeys[KEY_W]             = 0x57;
    win32->VirtualKeys[KEY_X]             = 0x58;
    win32->VirtualKeys[KEY_Y]             = 0x59;
    win32->VirtualKeys[KEY_Z]             = 0x5A;
    win32->VirtualKeys[KEY_LEFT_BRACKET]  = VK_OEM_4;
    win32->VirtualKeys[KEY_BACKSLASH]     = VK_OEM_5;
    win32->VirtualKeys[KEY_RIGHT_BRACKET] = VK_OEM_6;
    win32->VirtualKeys[KEY_GRAVE_ACCENT]  = VK_OEM_3;
    win32->VirtualKeys[KEY_ESCAPE]        = VK_ESCAPE;
    win32->VirtualKeys[KEY_ENTER]         = VK_RETURN;
    win32->VirtualKeys[KEY_TAB]           = VK_TAB;
    win32->VirtualKeys[KEY_BACKSPACE]     = VK_BACK;
    win32->VirtualKeys[KEY_INSERT]        = VK_INSERT;
    win32->VirtualKeys[KEY_DELETE]        = VK_DELETE;
    win32->VirtualKeys[KEY_RIGHT]         = VK_RIGHT;
    win32->VirtualKeys[KEY_LEFT]          = VK_LEFT;
    win32->VirtualKeys[KEY_DOWN]          = VK_DOWN;
    win32->VirtualKeys[KEY_UP]            = VK_UP;
    win32->VirtualKeys[KEY_PAGE_UP]       = VK_PRIOR;
    win32->VirtualKeys[KEY_PAGE_DOWN]     = VK_NEXT;
    win32->VirtualKeys[KEY_HOME]          = VK_HOME;
    win32->VirtualKeys[KEY_END]           = VK_END;
    win32->VirtualKeys[KEY_CAPS_LOCK]     = VK_CAPITAL;
    win32->VirtualKeys[KEY_SCROLL_LOCK]   = VK_SCROLL;
    win32->VirtualKeys[KEY_NUM_LOCK]      = VK_NUMLOCK;
    win32->VirtualKeys[KEY_PRINT_SCREEN]  = VK_SNAPSHOT;
    win32->VirtualKeys[KEY_PAUSE]         = VK_PAUSE;
    win32->VirtualKeys[KEY_F1]            = VK_F1;
    win32->VirtualKeys[KEY_F2]            = VK_F2;
    win32->VirtualKeys[KEY_F3]            = VK_F3;
    win32->VirtualKeys[KEY_F4]            = VK_F4;
    win32->VirtualKeys[KEY_F5]            = VK_F5;
    win32->VirtualKeys[KEY_F6]            = VK_F6;
    win32->VirtualKeys[KEY_F7]            = VK_F7;
    win32->VirtualKeys[KEY_F8]            = VK_F8;
    win32->VirtualKeys[KEY_F9]            = VK_F9;
    win32->VirtualKeys[KEY_F10]           = VK_F10;
    win32->VirtualKeys[KEY_F11]           = VK_F11;
    win32->VirtualKeys[KEY_F12]           = VK_F12;
    win32->VirtualKeys[KEY_F13]           = VK_F13;
    win32->VirtualKeys[KEY_F14]           = VK_F14;
    win32->VirtualKeys[KEY_F15]           = VK_F15;
    win32->VirtualKeys[KEY_F16]           = VK_F16;
    win32->VirtualKeys[KEY_F17]           = VK_F17;
    win32->VirtualKeys[KEY_F18]           = VK_F18;
    win32->VirtualKeys[KEY_F19]           = VK_F19;
    win32->VirtualKeys[KEY_F20]           = VK_F20;
    win32->VirtualKeys[KEY_F21]           = VK_F21;
    win32->VirtualKeys[KEY_F22]           = VK_F22;
    win32->VirtualKeys[KEY_F23]           = VK_F23;
    win32->VirtualKeys[KEY_F24]           = VK_F24;
    win32->VirtualKeys[KEY_F25]           = KEY_INVALID;
    win32->VirtualKeys[KEY_KP_0]          = VK_NUMPAD0;
    win32->VirtualKeys[KEY_KP_1]          = VK_NUMPAD1;
    win32->VirtualKeys[KEY_KP_2]          = VK_NUMPAD2;
    win32->VirtualKeys[KEY_KP_3]          = VK_NUMPAD3;
    win32->VirtualKeys[KEY_KP_4]          = VK_NUMPAD4;
    win32->VirtualKeys[KEY_KP_5]          = VK_NUMPAD5;
    win32->VirtualKeys[KEY_KP_6]          = VK_NUMPAD6;
    win32->VirtualKeys[KEY_KP_7]          = VK_NUMPAD7;
    win32->VirtualKeys[KEY_KP_8]          = VK_NUMPAD8;
    win32->VirtualKeys[KEY_KP_9]          = VK_NUMPAD9;
    win32->VirtualKeys[KEY_KP_DECIMAL]    = VK_DECIMAL;
    win32->VirtualKeys[KEY_KP_DIVIDE]     = VK_DIVIDE;
    win32->VirtualKeys[KEY_KP_MULTIPLY]   = VK_MULTIPLY;
    win32->VirtualKeys[KEY_KP_SUBTRACT]   = VK_SUBTRACT;
    win32->VirtualKeys[KEY_KP_ADD]        = VK_ADD;
    win32->VirtualKeys[KEY_KP_ENTER]      = KEY_INVALID;
    win32->VirtualKeys[KEY_KP_EQUAL]      = KEY_INVALID;
    win32->VirtualKeys[KEY_LEFT_SHIFT]    = VK_LSHIFT;
    win32->VirtualKeys[KEY_LEFT_CTRL]     = VK_LCONTROL;
    win32->VirtualKeys[KEY_LEFT_ALT]      = VK_LMENU;
    win32->VirtualKeys[KEY_LEFT_SUPER]    = KEY_INVALID;
    win32->VirtualKeys[KEY_RIGHT_SHIFT]   = VK_RSHIFT;
    win32->VirtualKeys[KEY_RIGHT_CTRL]    = VK_RCONTROL;
    win32->VirtualKeys[KEY_RIGHT_ALT]     = VK_RMENU;
    win32->VirtualKeys[KEY_RIGHT_SUPER]   = KEY_INVALID;
    win32->VirtualKeys[KEY_MENU]          = KEY_INVALID;

    BYTE state[256] = {0};
    for (s16 key = 0; key < KEY_COUNT; ++key)
    {
        const s32 vkey = win32->VirtualKeys[key];
        if (vkey == KEY_INVALID)
            continue;

        win32->Keycodes[vkey] = key;
        
        const UINT scancode = MapVirtualKeyW(vkey, MAPVK_VK_TO_VSC);
        if (scancode == 0)
            continue;
        
        win32->Scancodes[key] = scancode;

        wchar_t wkeyname[4];
        const s32 len = ToUnicode(vkey, scancode, state, wkeyname, ARRAY_COUNT(wkeyname), 0);
        if (len < 1)
            continue;

        utf16to8(wkeyname, win32->Keynames[key]);
    }    
}

bool key_up(whandle win, s16 key)
{
    ASSERT(key < KEY_COUNT);
    return !keydown(win, key);
}

bool key_down(whandle win, s16 key)
{
    ASSERT(key < KEY_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return bitcheck(win32->Keys.Buckets, key);
}

bool key_pressed(whandle win, s16 key)
{
    ASSERT(key < KEY_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return bitcheck(win32->KeysPressed.Buckets, key);
}

bool key_released(whandle win, s16 key)
{
    ASSERT(key < KEY_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return bitcheck(win32->KeysReleased.Buckets, key);
}

const char* key_name(whandle win, s16 key)
{
    ASSERT(key < KEY_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return win32->Keynames[key];
}

bool mouse_up(whandle win, s16 button)
{
    ASSERT(button < MOUSE_BUTTON_COUNT);
    return !mousedown(win, button);
}

bool mouse_down(whandle win, s16 button)
{
    ASSERT(button < MOUSE_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return BIT_CHECK(win32->MouseButtons, button);
}

bool mouse_pressed(whandle win, s16 button)
{
    ASSERT(button < MOUSE_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return BIT_CHECK(win32->MouseButtonsPressed, button);
}

bool mouse_released(whandle win, s16 button)
{
    ASSERT(button < MOUSE_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return BIT_CHECK(win32->MouseButtonsReleased, button);
}

bool gamepad_up(whandle win, u8 gamepad, s16 button)
{
    ASSERT(button < GAMEPAD_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return false;
}

bool gamepad_down(whandle win, u8 gamepad, s16 button)
{
    ASSERT(button < GAMEPAD_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return false;
}

bool gamepad_pressed(whandle win, u8 gamepad, s16 button)
{
    ASSERT(button < GAMEPAD_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return false;
}

bool gamepad_released(whandle win, u8 gamepad, s16 button)
{
    ASSERT(button < GAMEPAD_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return false;
}

f32 mouse_axis(whandle win, s16 axis)
{
    ASSERT(axis < MOUSE_AXIS_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return win32->MouseAxes[axis];
}

f32 gamepad_axis(whandle win, u8 gamepad, s16 gamepadAxis)
{
    ASSERT(gamepadAxis < GAMEPAD_AXIS_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return 0.0f;
}
