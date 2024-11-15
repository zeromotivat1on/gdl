#include "pch.h"
#include "str.h"
#include "input.h"
#include "win32_win.h"

void key_tables_init()
{
    memset(g_input_tables.virtual_keys, KEY_INVALID, sizeof(g_input_tables.virtual_keys));
    memset(g_input_tables.scancodes, KEY_INVALID, sizeof(g_input_tables.scancodes));
    memset(g_input_tables.keycodes, KEY_INVALID, sizeof(g_input_tables.keycodes));
    memset(g_input_tables.keynames, 0, sizeof(g_input_tables.keynames));

    g_input_tables.virtual_keys[KEY_SPACE]         = VK_SPACE;
    g_input_tables.virtual_keys[KEY_APOSTROPHE]    = VK_OEM_7;
    g_input_tables.virtual_keys[KEY_COMMA]         = VK_OEM_COMMA;
    g_input_tables.virtual_keys[KEY_MINUS]         = VK_OEM_MINUS;
    g_input_tables.virtual_keys[KEY_PERIOD]        = VK_OEM_PERIOD;
    g_input_tables.virtual_keys[KEY_SLASH]         = VK_OEM_2;
    g_input_tables.virtual_keys[KEY_0]             = 0x30;
    g_input_tables.virtual_keys[KEY_1]             = 0x31;
    g_input_tables.virtual_keys[KEY_2]             = 0x32;
    g_input_tables.virtual_keys[KEY_3]             = 0x33;
    g_input_tables.virtual_keys[KEY_4]             = 0x34;
    g_input_tables.virtual_keys[KEY_5]             = 0x35;
    g_input_tables.virtual_keys[KEY_6]             = 0x36;
    g_input_tables.virtual_keys[KEY_7]             = 0x37;
    g_input_tables.virtual_keys[KEY_8]             = 0x38;
    g_input_tables.virtual_keys[KEY_9]             = 0x39;
    g_input_tables.virtual_keys[KEY_SEMICOLON]     = VK_OEM_1;
    g_input_tables.virtual_keys[KEY_EQUAL]         = VK_OEM_PLUS;
    g_input_tables.virtual_keys[KEY_A]             = 0x41;
    g_input_tables.virtual_keys[KEY_B]             = 0x42;
    g_input_tables.virtual_keys[KEY_C]             = 0x43;
    g_input_tables.virtual_keys[KEY_D]             = 0x44;
    g_input_tables.virtual_keys[KEY_E]             = 0x45;
    g_input_tables.virtual_keys[KEY_F]             = 0x46;
    g_input_tables.virtual_keys[KEY_G]             = 0x47;
    g_input_tables.virtual_keys[KEY_H]             = 0x48;
    g_input_tables.virtual_keys[KEY_I]             = 0x49;
    g_input_tables.virtual_keys[KEY_J]             = 0x4A;
    g_input_tables.virtual_keys[KEY_K]             = 0x4B;
    g_input_tables.virtual_keys[KEY_L]             = 0x4C;
    g_input_tables.virtual_keys[KEY_M]             = 0x4D;
    g_input_tables.virtual_keys[KEY_N]             = 0x4E;
    g_input_tables.virtual_keys[KEY_O]             = 0x4F;
    g_input_tables.virtual_keys[KEY_P]             = 0x50;
    g_input_tables.virtual_keys[KEY_Q]             = 0x51;
    g_input_tables.virtual_keys[KEY_R]             = 0x52;
    g_input_tables.virtual_keys[KEY_S]             = 0x53;
    g_input_tables.virtual_keys[KEY_T]             = 0x54;
    g_input_tables.virtual_keys[KEY_U]             = 0x55;
    g_input_tables.virtual_keys[KEY_V]             = 0x56;
    g_input_tables.virtual_keys[KEY_W]             = 0x57;
    g_input_tables.virtual_keys[KEY_X]             = 0x58;
    g_input_tables.virtual_keys[KEY_Y]             = 0x59;
    g_input_tables.virtual_keys[KEY_Z]             = 0x5A;
    g_input_tables.virtual_keys[KEY_LEFT_BRACKET]  = VK_OEM_4;
    g_input_tables.virtual_keys[KEY_BACKSLASH]     = VK_OEM_5;
    g_input_tables.virtual_keys[KEY_RIGHT_BRACKET] = VK_OEM_6;
    g_input_tables.virtual_keys[KEY_GRAVE_ACCENT]  = VK_OEM_3;
    g_input_tables.virtual_keys[KEY_ESCAPE]        = VK_ESCAPE;
    g_input_tables.virtual_keys[KEY_ENTER]         = VK_RETURN;
    g_input_tables.virtual_keys[KEY_TAB]           = VK_TAB;
    g_input_tables.virtual_keys[KEY_BACKSPACE]     = VK_BACK;
    g_input_tables.virtual_keys[KEY_INSERT]        = VK_INSERT;
    g_input_tables.virtual_keys[KEY_DELETE]        = VK_DELETE;
    g_input_tables.virtual_keys[KEY_RIGHT]         = VK_RIGHT;
    g_input_tables.virtual_keys[KEY_LEFT]          = VK_LEFT;
    g_input_tables.virtual_keys[KEY_DOWN]          = VK_DOWN;
    g_input_tables.virtual_keys[KEY_UP]            = VK_UP;
    g_input_tables.virtual_keys[KEY_PAGE_UP]       = VK_PRIOR;
    g_input_tables.virtual_keys[KEY_PAGE_DOWN]     = VK_NEXT;
    g_input_tables.virtual_keys[KEY_HOME]          = VK_HOME;
    g_input_tables.virtual_keys[KEY_END]           = VK_END;
    g_input_tables.virtual_keys[KEY_CAPS_LOCK]     = VK_CAPITAL;
    g_input_tables.virtual_keys[KEY_SCROLL_LOCK]   = VK_SCROLL;
    g_input_tables.virtual_keys[KEY_NUM_LOCK]      = VK_NUMLOCK;
    g_input_tables.virtual_keys[KEY_PRINT_SCREEN]  = VK_SNAPSHOT;
    g_input_tables.virtual_keys[KEY_PAUSE]         = VK_PAUSE;
    g_input_tables.virtual_keys[KEY_F1]            = VK_F1;
    g_input_tables.virtual_keys[KEY_F2]            = VK_F2;
    g_input_tables.virtual_keys[KEY_F3]            = VK_F3;
    g_input_tables.virtual_keys[KEY_F4]            = VK_F4;
    g_input_tables.virtual_keys[KEY_F5]            = VK_F5;
    g_input_tables.virtual_keys[KEY_F6]            = VK_F6;
    g_input_tables.virtual_keys[KEY_F7]            = VK_F7;
    g_input_tables.virtual_keys[KEY_F8]            = VK_F8;
    g_input_tables.virtual_keys[KEY_F9]            = VK_F9;
    g_input_tables.virtual_keys[KEY_F10]           = VK_F10;
    g_input_tables.virtual_keys[KEY_F11]           = VK_F11;
    g_input_tables.virtual_keys[KEY_F12]           = VK_F12;
    g_input_tables.virtual_keys[KEY_F13]           = VK_F13;
    g_input_tables.virtual_keys[KEY_F14]           = VK_F14;
    g_input_tables.virtual_keys[KEY_F15]           = VK_F15;
    g_input_tables.virtual_keys[KEY_F16]           = VK_F16;
    g_input_tables.virtual_keys[KEY_F17]           = VK_F17;
    g_input_tables.virtual_keys[KEY_F18]           = VK_F18;
    g_input_tables.virtual_keys[KEY_F19]           = VK_F19;
    g_input_tables.virtual_keys[KEY_F20]           = VK_F20;
    g_input_tables.virtual_keys[KEY_F21]           = VK_F21;
    g_input_tables.virtual_keys[KEY_F22]           = VK_F22;
    g_input_tables.virtual_keys[KEY_F23]           = VK_F23;
    g_input_tables.virtual_keys[KEY_F24]           = VK_F24;
    g_input_tables.virtual_keys[KEY_F25]           = KEY_INVALID;
    g_input_tables.virtual_keys[KEY_KP_0]          = VK_NUMPAD0;
    g_input_tables.virtual_keys[KEY_KP_1]          = VK_NUMPAD1;
    g_input_tables.virtual_keys[KEY_KP_2]          = VK_NUMPAD2;
    g_input_tables.virtual_keys[KEY_KP_3]          = VK_NUMPAD3;
    g_input_tables.virtual_keys[KEY_KP_4]          = VK_NUMPAD4;
    g_input_tables.virtual_keys[KEY_KP_5]          = VK_NUMPAD5;
    g_input_tables.virtual_keys[KEY_KP_6]          = VK_NUMPAD6;
    g_input_tables.virtual_keys[KEY_KP_7]          = VK_NUMPAD7;
    g_input_tables.virtual_keys[KEY_KP_8]          = VK_NUMPAD8;
    g_input_tables.virtual_keys[KEY_KP_9]          = VK_NUMPAD9;
    g_input_tables.virtual_keys[KEY_KP_DECIMAL]    = VK_DECIMAL;
    g_input_tables.virtual_keys[KEY_KP_DIVIDE]     = VK_DIVIDE;
    g_input_tables.virtual_keys[KEY_KP_MULTIPLY]   = VK_MULTIPLY;
    g_input_tables.virtual_keys[KEY_KP_SUBTRACT]   = VK_SUBTRACT;
    g_input_tables.virtual_keys[KEY_KP_ADD]        = VK_ADD;
    g_input_tables.virtual_keys[KEY_KP_ENTER]      = KEY_INVALID;
    g_input_tables.virtual_keys[KEY_KP_EQUAL]      = KEY_INVALID;
    g_input_tables.virtual_keys[KEY_LEFT_SHIFT]    = VK_LSHIFT;
    g_input_tables.virtual_keys[KEY_LEFT_CTRL]     = VK_LCONTROL;
    g_input_tables.virtual_keys[KEY_LEFT_ALT]      = VK_LMENU;
    g_input_tables.virtual_keys[KEY_LEFT_SUPER]    = KEY_INVALID;
    g_input_tables.virtual_keys[KEY_RIGHT_SHIFT]   = VK_RSHIFT;
    g_input_tables.virtual_keys[KEY_RIGHT_CTRL]    = VK_RCONTROL;
    g_input_tables.virtual_keys[KEY_RIGHT_ALT]     = VK_RMENU;
    g_input_tables.virtual_keys[KEY_RIGHT_SUPER]   = KEY_INVALID;
    g_input_tables.virtual_keys[KEY_MENU]          = KEY_INVALID;

    BYTE state[256] = {0};
    for (s16 key = 0; key < KEY_COUNT; ++key)
    {
        const s32 vkey = g_input_tables.virtual_keys[key];
        if (vkey == KEY_INVALID)
            continue;

        g_input_tables.keycodes[vkey] = key;
        
        const UINT scancode = MapVirtualKeyW(vkey, MAPVK_VK_TO_VSC);
        if (scancode == 0)
            continue;
        
        g_input_tables.scancodes[key] = scancode;

        wchar_t wkeyname[4];
        const s32 len = ToUnicode(vkey, scancode, state, wkeyname, ARRAY_COUNT(wkeyname), 0);
        if (len < 1)
            continue;

        utf16_to_utf8(wkeyname, g_input_tables.keynames[key]);
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

const char* key_name(s16 key)
{
    PANIC(key >= KEY_COUNT);
    return g_input_tables.keynames[key];
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

s16 mouse_axis(hwindow win, s16 axis)
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
