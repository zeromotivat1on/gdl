#include "pch.h"
#include "msg.h"
#include <cstdio>

void* stdouthandle()
{
    static void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    return handle;
}

void msgva(void* outstream, MsgCategory category, const char* msg, va_list args)
{
    static char buffer[2][2048];
    ASSERT(outstream);

    char* vamsg = buffer[0];
    char* fmtmsg = buffer[1];

    vsnprintf(vamsg, sizeof(buffer[0]), msg, args);
    sprintf(fmtmsg, "[%s]: %s\n", msgnames[category], vamsg);

    WriteFile(outstream, fmtmsg, (DWORD)strlen(fmtmsg), nullptr, nullptr);
}
