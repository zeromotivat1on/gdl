#include "pch.h"
#include "str.h"
#include "input.h"
#include "win32_win.h"

void window_key_tables_init(void* win)
{
    Win32Window* win32 = (Win32Window*)win;

    memset(win32->virtual_keys, KEY_INVALID, sizeof(win32->virtual_keys));
    memset(win32->scancodes, KEY_INVALID, sizeof(win32->scancodes));
    memset(win32->keycodes, KEY_INVALID, sizeof(win32->keycodes));
    memset(win32->keynames, 0, sizeof(win32->keynames));

    win32->virtual_keys[KEY_SPACE]         = VK_SPACE;
    win32->virtual_keys[KEY_APOSTROPHE]    = VK_OEM_7;
    win32->virtual_keys[KEY_COMMA]         = VK_OEM_COMMA;
    win32->virtual_keys[KEY_MINUS]         = VK_OEM_MINUS;
    win32->virtual_keys[KEY_PERIOD]        = VK_OEM_PERIOD;
    win32->virtual_keys[KEY_SLASH]         = VK_OEM_2;
    win32->virtual_keys[KEY_0]             = 0x30;
    win32->virtual_keys[KEY_1]             = 0x31;
    win32->virtual_keys[KEY_2]             = 0x32;
    win32->virtual_keys[KEY_3]             = 0x33;
    win32->virtual_keys[KEY_4]             = 0x34;
    win32->virtual_keys[KEY_5]             = 0x35;
    win32->virtual_keys[KEY_6]             = 0x36;
    win32->virtual_keys[KEY_7]             = 0x37;
    win32->virtual_keys[KEY_8]             = 0x38;
    win32->virtual_keys[KEY_9]             = 0x39;
    win32->virtual_keys[KEY_SEMICOLON]     = VK_OEM_1;
    win32->virtual_keys[KEY_EQUAL]         = VK_OEM_PLUS;
    win32->virtual_keys[KEY_A]             = 0x41;
    win32->virtual_keys[KEY_B]             = 0x42;
    win32->virtual_keys[KEY_C]             = 0x43;
    win32->virtual_keys[KEY_D]             = 0x44;
    win32->virtual_keys[KEY_E]             = 0x45;
    win32->virtual_keys[KEY_F]             = 0x46;
    win32->virtual_keys[KEY_G]             = 0x47;
    win32->virtual_keys[KEY_H]             = 0x48;
    win32->virtual_keys[KEY_I]             = 0x49;
    win32->virtual_keys[KEY_J]             = 0x4A;
    win32->virtual_keys[KEY_K]             = 0x4B;
    win32->virtual_keys[KEY_L]             = 0x4C;
    win32->virtual_keys[KEY_M]             = 0x4D;
    win32->virtual_keys[KEY_N]             = 0x4E;
    win32->virtual_keys[KEY_O]             = 0x4F;
    win32->virtual_keys[KEY_P]             = 0x50;
    win32->virtual_keys[KEY_Q]             = 0x51;
    win32->virtual_keys[KEY_R]             = 0x52;
    win32->virtual_keys[KEY_S]             = 0x53;
    win32->virtual_keys[KEY_T]             = 0x54;
    win32->virtual_keys[KEY_U]             = 0x55;
    win32->virtual_keys[KEY_V]             = 0x56;
    win32->virtual_keys[KEY_W]             = 0x57;
    win32->virtual_keys[KEY_X]             = 0x58;
    win32->virtual_keys[KEY_Y]             = 0x59;
    win32->virtual_keys[KEY_Z]             = 0x5A;
    win32->virtual_keys[KEY_LEFT_BRACKET]  = VK_OEM_4;
    win32->virtual_keys[KEY_BACKSLASH]     = VK_OEM_5;
    win32->virtual_keys[KEY_RIGHT_BRACKET] = VK_OEM_6;
    win32->virtual_keys[KEY_GRAVE_ACCENT]  = VK_OEM_3;
    win32->virtual_keys[KEY_ESCAPE]        = VK_ESCAPE;
    win32->virtual_keys[KEY_ENTER]         = VK_RETURN;
    win32->virtual_keys[KEY_TAB]           = VK_TAB;
    win32->virtual_keys[KEY_BACKSPACE]     = VK_BACK;
    win32->virtual_keys[KEY_INSERT]        = VK_INSERT;
    win32->virtual_keys[KEY_DELETE]        = VK_DELETE;
    win32->virtual_keys[KEY_RIGHT]         = VK_RIGHT;
    win32->virtual_keys[KEY_LEFT]          = VK_LEFT;
    win32->virtual_keys[KEY_DOWN]          = VK_DOWN;
    win32->virtual_keys[KEY_UP]            = VK_UP;
    win32->virtual_keys[KEY_PAGE_UP]       = VK_PRIOR;
    win32->virtual_keys[KEY_PAGE_DOWN]     = VK_NEXT;
    win32->virtual_keys[KEY_HOME]          = VK_HOME;
    win32->virtual_keys[KEY_END]           = VK_END;
    win32->virtual_keys[KEY_CAPS_LOCK]     = VK_CAPITAL;
    win32->virtual_keys[KEY_SCROLL_LOCK]   = VK_SCROLL;
    win32->virtual_keys[KEY_NUM_LOCK]      = VK_NUMLOCK;
    win32->virtual_keys[KEY_PRINT_SCREEN]  = VK_SNAPSHOT;
    win32->virtual_keys[KEY_PAUSE]         = VK_PAUSE;
    win32->virtual_keys[KEY_F1]            = VK_F1;
    win32->virtual_keys[KEY_F2]            = VK_F2;
    win32->virtual_keys[KEY_F3]            = VK_F3;
    win32->virtual_keys[KEY_F4]            = VK_F4;
    win32->virtual_keys[KEY_F5]            = VK_F5;
    win32->virtual_keys[KEY_F6]            = VK_F6;
    win32->virtual_keys[KEY_F7]            = VK_F7;
    win32->virtual_keys[KEY_F8]            = VK_F8;
    win32->virtual_keys[KEY_F9]            = VK_F9;
    win32->virtual_keys[KEY_F10]           = VK_F10;
    win32->virtual_keys[KEY_F11]           = VK_F11;
    win32->virtual_keys[KEY_F12]           = VK_F12;
    win32->virtual_keys[KEY_F13]           = VK_F13;
    win32->virtual_keys[KEY_F14]           = VK_F14;
    win32->virtual_keys[KEY_F15]           = VK_F15;
    win32->virtual_keys[KEY_F16]           = VK_F16;
    win32->virtual_keys[KEY_F17]           = VK_F17;
    win32->virtual_keys[KEY_F18]           = VK_F18;
    win32->virtual_keys[KEY_F19]           = VK_F19;
    win32->virtual_keys[KEY_F20]           = VK_F20;
    win32->virtual_keys[KEY_F21]           = VK_F21;
    win32->virtual_keys[KEY_F22]           = VK_F22;
    win32->virtual_keys[KEY_F23]           = VK_F23;
    win32->virtual_keys[KEY_F24]           = VK_F24;
    win32->virtual_keys[KEY_F25]           = KEY_INVALID;
    win32->virtual_keys[KEY_KP_0]          = VK_NUMPAD0;
    win32->virtual_keys[KEY_KP_1]          = VK_NUMPAD1;
    win32->virtual_keys[KEY_KP_2]          = VK_NUMPAD2;
    win32->virtual_keys[KEY_KP_3]          = VK_NUMPAD3;
    win32->virtual_keys[KEY_KP_4]          = VK_NUMPAD4;
    win32->virtual_keys[KEY_KP_5]          = VK_NUMPAD5;
    win32->virtual_keys[KEY_KP_6]          = VK_NUMPAD6;
    win32->virtual_keys[KEY_KP_7]          = VK_NUMPAD7;
    win32->virtual_keys[KEY_KP_8]          = VK_NUMPAD8;
    win32->virtual_keys[KEY_KP_9]          = VK_NUMPAD9;
    win32->virtual_keys[KEY_KP_DECIMAL]    = VK_DECIMAL;
    win32->virtual_keys[KEY_KP_DIVIDE]     = VK_DIVIDE;
    win32->virtual_keys[KEY_KP_MULTIPLY]   = VK_MULTIPLY;
    win32->virtual_keys[KEY_KP_SUBTRACT]   = VK_SUBTRACT;
    win32->virtual_keys[KEY_KP_ADD]        = VK_ADD;
    win32->virtual_keys[KEY_KP_ENTER]      = KEY_INVALID;
    win32->virtual_keys[KEY_KP_EQUAL]      = KEY_INVALID;
    win32->virtual_keys[KEY_LEFT_SHIFT]    = VK_LSHIFT;
    win32->virtual_keys[KEY_LEFT_CTRL]     = VK_LCONTROL;
    win32->virtual_keys[KEY_LEFT_ALT]      = VK_LMENU;
    win32->virtual_keys[KEY_LEFT_SUPER]    = KEY_INVALID;
    win32->virtual_keys[KEY_RIGHT_SHIFT]   = VK_RSHIFT;
    win32->virtual_keys[KEY_RIGHT_CTRL]    = VK_RCONTROL;
    win32->virtual_keys[KEY_RIGHT_ALT]     = VK_RMENU;
    win32->virtual_keys[KEY_RIGHT_SUPER]   = KEY_INVALID;
    win32->virtual_keys[KEY_MENU]          = KEY_INVALID;

    BYTE state[256] = {0};
    for (s16 key = 0; key < KEY_COUNT; ++key)
    {
        const s32 vkey = win32->virtual_keys[key];
        if (vkey == KEY_INVALID)
            continue;

        win32->keycodes[vkey] = key;
        
        const UINT scancode = MapVirtualKeyW(vkey, MAPVK_VK_TO_VSC);
        if (scancode == 0)
            continue;
        
        win32->scancodes[key] = scancode;

        wchar_t wkeyname[4];
        const s32 len = ToUnicode(vkey, scancode, state, wkeyname, ARRAY_COUNT(wkeyname), 0);
        if (len < 1)
            continue;

        utf16_to_utf8(wkeyname, win32->keynames[key]);
    }    
}

bool key_up(hwindow win, s16 key)
{
    PANIC(key >= KEY_COUNT);
    return !key_down(win, key);
}

bool key_down(hwindow win, s16 key)
{
    PANIC(key >= KEY_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return bit_check(win32->keys.buckets, key);
}

bool key_pressed(hwindow win, s16 key)
{
    PANIC(key >= KEY_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return bit_check(win32->keys_pressed.buckets, key);
}

bool key_released(hwindow win, s16 key)
{
    PANIC(key >= KEY_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return bit_check(win32->keys_released.buckets, key);
}

const char* key_name(hwindow win, s16 key)
{
    PANIC(key >= KEY_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return win32->keynames[key];
}

bool mouse_up(hwindow win, s16 button)
{
    PANIC(button >= MOUSE_BUTTON_COUNT);
    return !mouse_down(win, button);
}

bool mouse_down(hwindow win, s16 button)
{
    PANIC(button >= MOUSE_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return BIT_CHECK(win32->mouse_buttons, button);
}

bool mouse_pressed(hwindow win, s16 button)
{
    PANIC(button >= MOUSE_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return BIT_CHECK(win32->mouse_buttons_pressed, button);
}

bool mouse_released(hwindow win, s16 button)
{
    PANIC(button >= MOUSE_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return BIT_CHECK(win32->mouse_buttons_released, button);
}

bool gamepad_up(hwindow win, u8 gamepad, s16 button)
{
    PANIC(button >= GAMEPAD_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return false;
}

bool gamepad_down(hwindow win, u8 gamepad, s16 button)
{
    PANIC(button >= GAMEPAD_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return false;
}

bool gamepad_pressed(hwindow win, u8 gamepad, s16 button)
{
    PANIC(button >= GAMEPAD_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return false;
}

bool gamepad_released(hwindow win, u8 gamepad, s16 button)
{
    PANIC(button >= GAMEPAD_BUTTON_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return false;
}

f32 mouse_axis(hwindow win, s16 axis)
{
    PANIC(axis >= MOUSE_AXIS_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return win32->mouse_axes[axis];
}

f32 gamepad_axis(hwindow win, u8 gamepad, s16 gamepadAxis)
{
    PANIC(gamepadAxis >= GAMEPAD_AXIS_COUNT);
    Win32Window* win32 = (Win32Window*)win;
    return 0.0f;
}
