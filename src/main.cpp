#include "pch.h"
#include "include/gdl.h"
#include <stdio.h>

#if 1
int main()
{
    WindowInfo winfo = STRUCT_ZERO(WindowInfo);
    winfo.Title = "GDL Window";
    winfo.Width = 1280;
    winfo.Height = 720;
    winfo.X = 400;
    winfo.Y = 100;

    void* win = ::operator new(WIN_ALLOC_SIZE);
    memset(win, 0, WIN_ALLOC_SIZE);

    if (!wincreate(&winfo, win))
    {
        return -1;
    }

    winkeymaps(win);
    
    while(!winclosed(win))
    {
        winupdate(win);

        for (s16 key = 0; key < KEY_COUNT; ++key)
        {
            if (keypressed(win, key))
            {
                printf("Key pressed: %s\n", keyname(win, key));
            }
        }

        for (s16 button = 0; button < MOUSE_BUTTON_COUNT; ++button)
        {
            if (mousepressed(win, button))
            {
                printf("Mouse button pressed: %d\n", button);
            }
        }

        thsleep(33);
    }

    return 0;
}
#endif
