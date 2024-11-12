#include "pch.h"
#include "win.h"
#include "str.h"
#include "win32_win.h"
#include <malloc.h>
#include <windowsx.h>

const u16 WINDOW_ALLOC_SIZE = sizeof(Win32Window);

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

static LRESULT CALLBACK win32_window_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    Win32Window* win32 = (Win32Window*)GetPropW(hwnd, L"gdl");
    if (!win32)
    {
        return DefWindowProcW(hwnd, umsg, wparam, lparam);
    }
    
    switch(umsg)
    {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            if (const s16 key = win32->keycodes[wparam]; key > 0)
                bit_set(win32->keys.buckets, key);
            break;
        }

        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            if (const s16 key = win32->keycodes[wparam]; key > 0)
                bit_clear(win32->keys.buckets, key);
            break;
        }

    	case WM_LBUTTONDOWN: BIT_SET(win32->mouse_buttons, MOUSE_LEFT); break;
    	case WM_RBUTTONDOWN: BIT_SET(win32->mouse_buttons, MOUSE_RIGHT); break;
    	case WM_MBUTTONDOWN: BIT_SET(win32->mouse_buttons, MOUSE_MIDDLE); break;
    	case WM_XBUTTONDOWN: break;
    	case WM_LBUTTONUP: BIT_CLEAR(win32->mouse_buttons, MOUSE_LEFT); break; 
    	case WM_RBUTTONUP: BIT_CLEAR(win32->mouse_buttons, MOUSE_RIGHT); break; 
    	case WM_MBUTTONUP: BIT_CLEAR(win32->mouse_buttons, MOUSE_MIDDLE); break; 
    	case WM_XBUTTONUP: break;
    	case WM_MOUSEMOVE:
        {   
            win32->mouse_axes[MOUSE_X] = (f32)GET_X_LPARAM(lparam);
            win32->mouse_axes[MOUSE_Y] = (f32)GET_Y_LPARAM(lparam);
            break;
        }

        case WM_MOUSEWHEEL:
        {
            win32->mouse_axes[MOUSE_SCROLL_X] = 0.0f;
            win32->mouse_axes[MOUSE_SCROLL_Y] = GET_WHEEL_DELTA_WPARAM(wparam);
            break;
        }
    }
    
    return DefWindowProcW(hwnd, umsg, wparam, lparam);
}

bool window_create(hwindow win, WindowInfo* info)
{
    Win32Window* win32 = (Win32Window*)win;

    if (!win32->class_atom)
    {
        win32->class_name = L"gdl";

        WNDCLASSEXW wclass = STRUCT_ZERO(WNDCLASSEXW);
        wclass.cbSize = sizeof(wclass);
        wclass.style = CS_HREDRAW | CS_VREDRAW;
        wclass.lpfnWndProc = win32_window_proc;
        wclass.hInstance = win32->hinstance;
        wclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wclass.lpszClassName = win32->class_name;

        win32->class_atom = RegisterClassExW(&wclass);
    }

    if (!win32->hinstance)
    {
        win32->hinstance = (HINSTANCE)&__ImageBase;
    }

    static wchar_t wtitle[32];
    utf8_to_utf16(info->title, wtitle);
    ASSERT(win32->handle == NULL);

    win32->handle = CreateWindowExW(
        0,
        win32->class_name,
        wtitle,
        WS_OVERLAPPEDWINDOW,
        info->x,
        info->y,
        info->width,
        info->height,
        NULL,
        NULL,
        win32->hinstance,
        NULL
    );

    if (win32->handle == NULL)
        return false;

    SetPropW(win32->handle, L"gdl", win32);
    ShowWindow(win32->handle, SW_NORMAL);
    
    return true;
}

void window_destroy(hwindow win)
{
    Win32Window* win32 = (Win32Window*)win;
    DestroyWindow(win32->handle);
    UnregisterClassW(win32->class_name, win32->hinstance);
}

void window_update(hwindow win)
{
    Win32Window* win32 = (Win32Window*)win;
        
    win32->mouse_axes[MOUSE_SCROLL_X] = 0.0f;
    win32->mouse_axes[MOUSE_SCROLL_Y] = 0.0f;
    
    MSG msg = STRUCT_ZERO(MSG);
    msg.hwnd = win32->handle;

    while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Update pressed/released keys.
    {
        const u64 count = ARRAY_COUNT(win32->keys.buckets);
        
        u64* changes = (u64*)alloca(count * sizeof(u64));
        bit_xor(changes, win32->keys.buckets, win32->keys_last.buckets, count);

        u64* notbuckets = (u64*)alloca(count * sizeof(u64));
        bit_not(notbuckets, win32->keys.buckets, count);

        bit_and(win32->keys_pressed.buckets, changes, win32->keys.buckets, count);
        bit_and(win32->keys_released.buckets, changes, notbuckets, count);

        memcpy(&win32->keys_last, &win32->keys, sizeof(win32->keys));
    }

    // Update pressed/released mouse buttons.
    {
        const u8 changes = win32->mouse_buttons ^ win32->mouse_buttons_last;
        win32->mouse_buttons_pressed = changes & win32->mouse_buttons;
        win32->mouse_buttons_released = changes & (~win32->mouse_buttons);

        win32->mouse_buttons_last = win32->mouse_buttons;
    }

    // Update mouse offset.
    {
         win32->mouse_axes[MOUSE_OFFSET_X] = win32->mouse_axes[MOUSE_X] - win32->mouse_axes[MOUSE_LAST_X];
         win32->mouse_axes[MOUSE_OFFSET_Y] = win32->mouse_axes[MOUSE_LAST_Y] - win32->mouse_axes[MOUSE_Y];

         win32->mouse_axes[MOUSE_LAST_X] = win32->mouse_axes[MOUSE_X];
         win32->mouse_axes[MOUSE_LAST_Y] = win32->mouse_axes[MOUSE_Y];   
    }
    // TODO: gamepad.
}

void window_close(hwindow win)
{
    Win32Window* win32 = (Win32Window*)win;
    PostMessage(win32->handle, WM_CLOSE, 0, 0);
}

bool window_active(hwindow win)
{
    Win32Window* win32 = (Win32Window*)win;
    return IsWindow(win32->handle);
}

void window_size(hwindow win, u16* w, u16* h)
{
    Win32Window* win32 = (Win32Window*)win;
    RECT rect;
    if (GetWindowRect(win32->handle, &rect))
    {
        if (w) *w = (u16)(rect.right - rect.left);
        if (h) *h = (u16)(rect.bottom - rect.top);
    }
}

void window_size_inner(hwindow win, u16* w, u16* h)
{
    Win32Window* win32 = (Win32Window*)win;
    RECT rect;
    if (GetClientRect(win32->handle, &rect))
    {
        if (w) *w = (u16)(rect.right - rect.left);
        if (h) *h = (u16)(rect.bottom - rect.top);
    }
}

void* window_native(hwindow win)
{
    Win32Window* win32 = (Win32Window*)win;
    return win32->handle;
}

bool window_cursor_lock(hwindow win, bool lock)
{
    if (lock)
    {
        Win32Window* win32 = (Win32Window*)win;
        RECT rect;
        if (GetWindowRect(win32->handle, &rect))
        {
            return ClipCursor(&rect);
        }

        return false;
    }

    return ClipCursor(NULL);
}

s32 window_cursor_show(hwindow win, bool show)
{
    return ShowCursor(show);
}
