#include "pch.h"
#include "str.h"

void utf8_to_utf16(const char* src, wchar_t* dst)
{
    const s32 len = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
    if (len == 0)
        return;

    if (MultiByteToWideChar(CP_UTF8, 0, src, -1, (LPWSTR)dst, len) == 0)
        return;
}

void utf16_to_utf8(const wchar_t* src, char* dst)
{
    const s32 len = WideCharToMultiByte(CP_UTF8, 0, src, -1, NULL, 0, NULL, NULL);
    if (len == 0)
        return;

    if (WideCharToMultiByte(CP_UTF8, 0, src, -1, (LPSTR)dst, len, NULL, NULL) == 0)
        return;
}
