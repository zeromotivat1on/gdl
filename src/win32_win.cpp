#include "pch.h"
#include "win.h"
#include "str.h"
#include "win32_win.h"
#include <malloc.h>
#include <windowsx.h>

const u16 WINDOW_ALLOC_SIZE = sizeof(Win32Window);

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

static LRESULT CALLBACK win32_winproc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
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
            if (const s16 key = win32->Keycodes[wparam]; key > 0)
                bitset(win32->Keys.Buckets, key);
            break;
        }

        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            if (const s16 key = win32->Keycodes[wparam]; key > 0)
                bitclear(win32->Keys.Buckets, key);
            break;
        }

    	case WM_LBUTTONDOWN: BIT_SET(win32->MouseButtons, MOUSE_LEFT); break;
    	case WM_RBUTTONDOWN: BIT_SET(win32->MouseButtons, MOUSE_RIGHT); break;
    	case WM_MBUTTONDOWN: BIT_SET(win32->MouseButtons, MOUSE_MIDDLE); break;
    	case WM_XBUTTONDOWN: break;
    	case WM_LBUTTONUP: BIT_CLEAR(win32->MouseButtons, MOUSE_LEFT); break; 
    	case WM_RBUTTONUP: BIT_CLEAR(win32->MouseButtons, MOUSE_RIGHT); break; 
    	case WM_MBUTTONUP: BIT_CLEAR(win32->MouseButtons, MOUSE_MIDDLE); break; 
    	case WM_XBUTTONUP: break;
    	case WM_MOUSEMOVE:
        {   
            win32->MouseAxes[MOUSE_X] = (f32)GET_X_LPARAM(lparam);
            win32->MouseAxes[MOUSE_Y] = (f32)GET_Y_LPARAM(lparam);
            break;
        }

        case WM_MOUSEWHEEL:
        {
            win32->MouseAxes[MOUSE_SCROLL_X] = 0.0f;
            win32->MouseAxes[MOUSE_SCROLL_Y] = GET_WHEEL_DELTA_WPARAM(wparam);
            break;
        }
    }
    
    return DefWindowProcW(hwnd, umsg, wparam, lparam);
}

bool wcreate(WindowInfo* info, whandle win)
{
    Win32Window* win32 = (Win32Window*)win;

    if (!win32->Class)
    {
        win32->ClassName = L"gdl";

        WNDCLASSEXW wclass = STRUCT_ZERO(WNDCLASSEXW);
        wclass.cbSize = sizeof(wclass);
        wclass.style = CS_HREDRAW | CS_VREDRAW;
        wclass.lpfnWndProc = win32_winproc;
        wclass.hInstance = win32->Instance;
        wclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wclass.lpszClassName = win32->ClassName;

        win32->Class = RegisterClassExW(&wclass);
    }

    if (!win32->Instance)
    {
        win32->Instance = (HINSTANCE)&__ImageBase;
    }

    static wchar_t wtitle[32];
    utf8to16(info->Title, wtitle);
    ASSERT(win32->Handle == NULL);

    win32->Handle = CreateWindowExW(
        0,
        win32->ClassName,
        wtitle,
        WS_OVERLAPPEDWINDOW,
        info->X,
        info->Y,
        info->Width,
        info->Height,
        NULL,
        NULL,
        win32->Instance,
        NULL
    );

    if (win32->Handle == NULL)
        return false;

    SetPropW(win32->Handle, L"gdl", win32);
    ShowWindow(win32->Handle, SW_NORMAL);
    
    return true;
}

void wdestroy(whandle win)
{
    Win32Window* win32 = (Win32Window*)win;
    DestroyWindow(win32->Handle);
    UnregisterClassW(win32->ClassName, win32->Instance);
}

void wupdate(whandle win)
{
    Win32Window* win32 = (Win32Window*)win;
        
    win32->MouseAxes[MOUSE_SCROLL_X] = 0.0f;
    win32->MouseAxes[MOUSE_SCROLL_Y] = 0.0f;
    
    MSG msg = STRUCT_ZERO(MSG);
    msg.hwnd = win32->Handle;

    while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Update pressed/released keys.
    {
        const u64 count = ARRAY_COUNT(win32->Keys.Buckets);
        
        u64* changes = (u64*)alloca(count * sizeof(u64));
        bitxor(changes, win32->Keys.Buckets, win32->KeysLast.Buckets, count);

        u64* notbuckets = (u64*)alloca(count * sizeof(u64));
        bitnot(notbuckets, win32->Keys.Buckets, count);

        bitand(win32->KeysPressed.Buckets, changes, win32->Keys.Buckets, count);
        bitand(win32->KeysReleased.Buckets, changes, notbuckets, count);

        memcpy(&win32->KeysLast, &win32->Keys, sizeof(win32->Keys));
    }

    // Update pressed/released mouse buttons.
    {
        const u8 changes = win32->MouseButtons ^ win32->MouseButtonsLast;
        win32->MouseButtonsPressed = changes & win32->MouseButtons;
        win32->MouseButtonsReleased = changes & (~win32->MouseButtons);

        win32->MouseButtonsLast = win32->MouseButtons;
    }

    // Update mouse offset.
    {
         win32->MouseAxes[MOUSE_OFFSET_X] = win32->MouseAxes[MOUSE_X] - win32->MouseAxes[MOUSE_LAST_X];
         win32->MouseAxes[MOUSE_OFFSET_Y] = win32->MouseAxes[MOUSE_LAST_Y] - win32->MouseAxes[MOUSE_Y];

         win32->MouseAxes[MOUSE_LAST_X] = win32->MouseAxes[MOUSE_X];
         win32->MouseAxes[MOUSE_LAST_Y] = win32->MouseAxes[MOUSE_Y];   
    }
    // TODO: gamepad.
}

void wclose(whandle win)
{
    Win32Window* win32 = (Win32Window*)win;
    PostMessage(win32->Handle, WM_CLOSE, 0, 0);
}

bool wactive(whandle win)
{
    Win32Window* win32 = (Win32Window*)win;
    return IsWindow(win32->Handle);
}

void wsize(whandle win, u16* w, u16* h)
{
    Win32Window* win32 = (Win32Window*)win;
    RECT rect;
    if (GetWindowRect(win32->Handle, &rect))
    {
        if (w) *w = (u16)(rect.right - rect.left);
        if (h) *h = (u16)(rect.bottom - rect.top);
    }
}

void wsizeinner(whandle win, u16* w, u16* h)
{
    Win32Window* win32 = (Win32Window*)win;
    RECT rect;
    if (GetClientRect(win32->Handle, &rect))
    {
        if (w) *w = (u16)(rect.right - rect.left);
        if (h) *h = (u16)(rect.bottom - rect.top);
    }
}

void* wnative(whandle win)
{
    Win32Window* win32 = (Win32Window*)win;
    return win32->Handle;
}

bool wcursor(whandle win, bool lock)
{
    Win32Window* win32 = (Win32Window*)win;
    RECT rect;
    if (GetWindowRect(win32->Handle, &rect))
    {
        return ClipCursor(&rect);
    }

    return false;
}
