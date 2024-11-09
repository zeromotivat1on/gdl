#include "pch.h"
#include "msg.h"

void* stdout()
{
    static void* stdouthandle = GetStdHandle(STD_OUTPUT_HANDLE)
    return stdouthandle;
}

void msgva(void* outstream, MsgCategory category, const char* msg, va_list args)
{
    static char buffer[2][2048];
    ASSERT(outstream);

    char* vamsg = buffer[0];
    char* fmtmsg = buffer[1];

    vsnprintf(vamsg, sizeof(buffer[0]), msg, args);
    sprintf(fmtmsg, "[%s]: %s\n", msgnames[category], vamsg);

    WriteFile(outstream, fmtmsg, strlen(fmtmsg), nullptr, nullptr);
}
