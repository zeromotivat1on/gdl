#pragma once

#include "win.h"

//
// TODO: add gamepad support.
//

// -----
// Types
// -----

enum ButtonAction : s8
{
    RELEASE = 0,
    PRESS   = 1,
};

enum Key : s16
{
    KEY_INVALID = -1,

    // Printable keys.
    KEY_SPACE = 0,
    KEY_APOSTROPHE,
    KEY_COMMA,
    KEY_MINUS,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_SEMICOLON,
    KEY_EQUAL,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_LEFT_BRACKET,
    KEY_BACKSLASH,
    KEY_RIGHT_BRACKET,
    KEY_GRAVE_ACCENT,

    // Function keys.
    KEY_ESCAPE,
    KEY_ENTER,
    KEY_TAB,
    KEY_BACKSPACE,
    KEY_INSERT,
    KEY_DELETE,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_HOME,
    KEY_END,
    KEY_CAPS_LOCK,
    KEY_SCROLL_LOCK,
    KEY_NUM_LOCK,
    KEY_PRINT_SCREEN,
    KEY_PAUSE,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_F16,
    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F20,
    KEY_F21,
    KEY_F22,
    KEY_F23,
    KEY_F24,
    KEY_F25,
    KEY_KP_0,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_DECIMAL,
    KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY,
    KEY_KP_SUBTRACT,
    KEY_KP_ADD,
    KEY_KP_ENTER,
    KEY_KP_EQUAL,
    KEY_LEFT_SHIFT,
    KEY_LEFT_CTRL,
    KEY_LEFT_ALT,
    KEY_LEFT_SUPER,
    KEY_RIGHT_SHIFT,
    KEY_RIGHT_CTRL,
    KEY_RIGHT_ALT,
    KEY_RIGHT_SUPER,
    KEY_MENU,

    KEY_COUNT,
};

enum MouseButton : s16
{
    MOUSE_BUTTON_INVALID = -1,

    MOUSE_LEFT = 0,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,

    MOUSE_BUTTON_COUNT,
};

enum GamepadButton : s16
{
    GAMEPAD_BUTTON_INVALID = -1,

    GAMEPAD_FACE_UP = 0,
    GAMEPAD_FACE_RIGHT,
    GAMEPAD_FACE_DOWN,
    GAMEPAD_FACE_LEFT,
    GAMEPAD_LB,
    GAMEPAD_RB,
    GAMEPAD_BACK,
    GAMEPAD_START,
    GAMEPAD_GUIDE,
    GAMEPAD_LTHUMB,
    GAMEPAD_RTHUMB,
    GAMEPAD_DPAD_UP,
    GAMEPAD_DPAD_RIGHT,
    GAMEPAD_DPAD_DOWN,
    GAMEPAD_DPAD_LEFT,

    GAMEPAD_BUTTON_COUNT,

    GAMEPAD_TRIANGLE = GAMEPAD_FACE_UP,
    GAMEPAD_CIRCLE = GAMEPAD_FACE_RIGHT,
    GAMEPAD_CROSS = GAMEPAD_FACE_DOWN,
    GAMEPAD_SQUARE = GAMEPAD_FACE_LEFT,

    GAMEPAD_Y = GAMEPAD_FACE_UP,
    GAMEPAD_B = GAMEPAD_FACE_RIGHT,
    GAMEPAD_A = GAMEPAD_FACE_DOWN,
    GAMEPAD_X = GAMEPAD_FACE_LEFT,
};

enum MouseAxis : s16
{
    MOUSE_AXIS_INVALID = -1,

    MOUSE_X = 0,
    MOUSE_Y,
    MOUSE_OFFSET_X,
    MOUSE_OFFSET_Y,
    MOUSE_SCROLL_X,
    MOUSE_SCROLL_Y,

    MOUSE_AXIS_COUNT,
};

enum GamepadAxis : s16
{
    GAMEPAD_AXIS_INVALID = -1,

    GAMEPAD_LX = 0,
    GAMEPAD_LY,
    GAMEPAD_RX,
    GAMEPAD_RY,
    GAMEPAD_LT,
    GAMEPAD_RT,

    GAMEPAD_AXIS_COUNT,
};

// -----
// Input
// -----

// Initialize input tables.
void    winkeymaps(winhandle win);

// Button states.

bool        keyup(winhandle win, s16 key);
bool        keydown(winhandle win, s16 key);
bool        keypressed(winhandle win, s16 key);
bool        keyreleased(winhandle win, s16 key);
const char* keyname(winhandle win, s16 key);

bool        mouseup(winhandle win, s16 button);
bool        mousedown(winhandle win, s16 button);
bool        mousepressed(winhandle win, s16 button);
bool        mousereleased(winhandle win, s16 button);

bool        gamepadup(winhandle win, u8 gamepad, s16 button);
bool        gamepaddown(winhandle win, u8 gamepad, s16 button);
bool        gamepadpressed(winhandle win, u8 gamepad, s16 button);
bool        gamepadreleased(winhandle win, u8 gamepad, s16 button);

// Axis values.

f32         mouseaxis(winhandle win, s16 axis);
f32         gamepadaxis(winhandle win, u8 gamepad, s16 axis);

