#include "pch.h"
#include "msg.h"
#include <cstdio>

void* stdout_handle()
{
    static void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    return handle;
}

void msg_va(void* stream, MsgCategory category, const char* msg, va_list args)
{
    static char buffer[2][2048];
    
    PANIC(!stream);

    char* va_msg = buffer[0];
    char* fmt_msg = buffer[1];

    vsnprintf(va_msg, sizeof(buffer[0]), msg, args);
    sprintf(fmt_msg, "[%s]: %s\n", MSG_NAMES[category], va_msg);

    WriteFile(stream, fmt_msg, (DWORD)strlen(fmt_msg), nullptr, nullptr);
}
