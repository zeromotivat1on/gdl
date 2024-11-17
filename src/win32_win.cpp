#include "pch.h"
#include "win.h"
#include "str.h"
#include "win32_win.h"
#include <malloc.h>
#include <windowsx.h>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

static LRESULT CALLBACK win32_window_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    Window* win = (Window*)GetPropW(hwnd, L"gdl");
    if (!win)
    {
        return DefWindowProcW(hwnd, umsg, wparam, lparam);
    }
    
    switch(umsg)
    {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            if (const s16 key = g_input_tables.keycodes[wparam]; key > 0)
                bit_set(win->keys.buckets, key);
            break;
        }

        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            if (const s16 key = g_input_tables.keycodes[wparam]; key > 0)
                bit_clear(win->keys.buckets, key);
            break;
        }

    	case WM_LBUTTONDOWN: BIT_SET(win->mouse_buttons, MOUSE_LEFT); break;
    	case WM_RBUTTONDOWN: BIT_SET(win->mouse_buttons, MOUSE_RIGHT); break;
    	case WM_MBUTTONDOWN: BIT_SET(win->mouse_buttons, MOUSE_MIDDLE); break;
    	case WM_XBUTTONDOWN: break;
    	case WM_LBUTTONUP: BIT_CLEAR(win->mouse_buttons, MOUSE_LEFT); break; 
    	case WM_RBUTTONUP: BIT_CLEAR(win->mouse_buttons, MOUSE_RIGHT); break; 
    	case WM_MBUTTONUP: BIT_CLEAR(win->mouse_buttons, MOUSE_MIDDLE); break; 
    	case WM_XBUTTONUP: break;

        case WM_MOUSEMOVE:
        {   
            win->mouse_axes[MOUSE_X] = GET_X_LPARAM(lparam);
            win->mouse_axes[MOUSE_Y] = GET_Y_LPARAM(lparam);
            break;
        }

        case WM_MOUSEWHEEL:
        {
            win->mouse_axes[MOUSE_SCROLL_X] = 0;
            win->mouse_axes[MOUSE_SCROLL_Y] = GET_WHEEL_DELTA_WPARAM(wparam);
            break;
        }
    }
    
    return DefWindowProcW(hwnd, umsg, wparam, lparam);
}

bool window_init(Window* win, WindowInfo* info)
{
    memset(win, 0, WINDOW_ALLOC_SIZE);
    
    if (!win->win32.class_atom)
    {
        win->win32.class_name = L"gdl";

        WNDCLASSEXW wclass = STRUCT_ZERO(WNDCLASSEXW);
        wclass.cbSize = sizeof(wclass);
        wclass.style = CS_HREDRAW | CS_VREDRAW;
        wclass.lpfnWndProc = win32_window_proc;
        wclass.hInstance = win->win32.hinstance;
        wclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wclass.lpszClassName = win->win32.class_name;

        win->win32.class_atom = RegisterClassExW(&wclass);
    }

    if (!win->win32.hinstance)
    {
        win->win32.hinstance = (HINSTANCE)&__ImageBase;
    }

    static wchar_t wtitle[32];
    utf8_to_utf16(info->title, wtitle);
    
    win->win32.hwnd = CreateWindowExW(
        0,
        win->win32.class_name,
        wtitle,
        WS_OVERLAPPEDWINDOW,
        info->x,
        info->y,
        info->width,
        info->height,
        NULL,
        NULL,
        win->win32.hinstance,
        NULL
    );

    if (win->win32.hwnd == NULL)
        return false;

    SetPropW(win->win32.hwnd, L"gdl", win);
    
    return true;
}

void window_show(Window* win)
{
    ShowWindow(win->win32.hwnd, SW_NORMAL);
}

void window_destroy(Window* win)
{
    DestroyWindow(win->win32.hwnd);
    UnregisterClassW(win->win32.class_name, win->win32.hinstance);
}

void window_update(Window* win)
{        
    win->mouse_axes[MOUSE_SCROLL_X] = 0;
    win->mouse_axes[MOUSE_SCROLL_Y] = 0;
    
    MSG msg = STRUCT_ZERO(MSG);
    msg.hwnd = win->win32.hwnd;

    while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Update keys.
    {
        const u64 count = ARRAY_COUNT(win->keys.buckets);
        
        u64* changes = (u64*)alloca(count * sizeof(u64));
        bit_xor(changes, win->keys.buckets, win->keys_last.buckets, count);

        u64* notbuckets = (u64*)alloca(count * sizeof(u64));
        bit_not(notbuckets, win->keys.buckets, count);

        bit_and(win->keys_pressed.buckets, changes, win->keys.buckets, count);
        bit_and(win->keys_released.buckets, changes, notbuckets, count);

        memcpy(&win->keys_last, &win->keys, sizeof(win->keys));
    }

    // Update mouse buttons.
    {
        const u8 changes = win->mouse_buttons ^ win->mouse_buttons_last;
        win->mouse_buttons_pressed = changes & win->mouse_buttons;
        win->mouse_buttons_released = changes & (~win->mouse_buttons);

        win->mouse_buttons_last = win->mouse_buttons;
    }

    // Update mouse axes.
    {
         win->mouse_axes[MOUSE_OFFSET_X] = win->mouse_axes[MOUSE_X] - win->mouse_axes[MOUSE_LAST_X];
         win->mouse_axes[MOUSE_OFFSET_Y] = win->mouse_axes[MOUSE_LAST_Y] - win->mouse_axes[MOUSE_Y];

         
         if (win->cursor_constrained)
         {
             u16 w, h;
             window_size_inner(win, &w, &h);
             
             POINT point;
             point.x = win->mouse_axes[MOUSE_LAST_X] = w / 2;
             point.y = win->mouse_axes[MOUSE_LAST_Y] = h / 2;

             ClientToScreen(win->win32.hwnd, &point);
             SetCursorPos(point.x, point.y);
         }
         else
         {
             win->mouse_axes[MOUSE_LAST_X] = win->mouse_axes[MOUSE_X];
             win->mouse_axes[MOUSE_LAST_Y] = win->mouse_axes[MOUSE_Y];
         }
    }

    // TODO: gamepad.
}

void window_close(Window* win)
{
    PostMessage(win->win32.hwnd, WM_CLOSE, 0, 0);
}

bool window_active(Window* win)
{
    return IsWindow(win->win32.hwnd);
}

void window_size(Window* win, u16* w, u16* h)
{
    RECT rect;
    if (GetWindowRect(win->win32.hwnd, &rect))
    {
        if (w) *w = (u16)(rect.right - rect.left);
        if (h) *h = (u16)(rect.bottom - rect.top);
    }
}

void window_size_inner(Window* win, u16* w, u16* h)
{
    RECT rect;
    if (GetClientRect(win->win32.hwnd, &rect))
    {
        if (w) *w = (u16)(rect.right - rect.left);
        if (h) *h = (u16)(rect.bottom - rect.top);
    }
}

void* window_native(Window* win)
{
    return win->win32.hwnd;
}

void window_set_char_callback(Window* win, window_char_callback callback)
{
    win->callbacks.character = callback;
}

bool window_cursor_lock(Window* win, bool lock)
{
    if (lock)
    {
        RECT rect;
        if (GetWindowRect(win->win32.hwnd, &rect))
        {
            return ClipCursor(&rect);
        }

        return false;
    }

    return ClipCursor(NULL);
}

s32 window_cursor_show(Window* win, bool show)
{
    return ShowCursor(show);
}

void window_cursor_constrain(Window* win, bool constrain)
{
    win->cursor_constrained = constrain;
}

void window_cursor_pos_absolute(Window* win, u16* x, u16* y)
{
    POINT point;
    GetCursorPos(&point);

    if (x) *x = (u16)point.x;
    if (y) *y = (u16)point.y;
}

void window_cursor_pos_relative(Window* win, u16* x, u16* y)
{
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(win->win32.hwnd, &point);

    if (x) *x = (u16)point.x;
    if (y) *y = (u16)point.y;
}
