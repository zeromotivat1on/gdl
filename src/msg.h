#pragma once

enum MsgCategory
{
    MSG_VERBOSE,
    MSG_DEBUG,
    MSG_LOG,
    MSG_WARNING,
    MSG_ERROR,
    MSG_CRITICAL,
    MSG_COUNT
};

inline const char* msgnames[MSG_COUNT] = { "Verbose", "Debug", "Log", "Warning", "Error", "Critical" };

void* stdout(); // standart output handle

void msgva(void* outstream, MsgCategory category, const char* msg, va_list args);

inline void msg(void* outstream, MsgCategory category, const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msgva(outstream, category, msg, args);
    va_end(args);
}

inline void msg(MsgCategory category, const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msgva(stdout(), category, msg, args);
    va_end(args);
}

inline void msgverb(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msgva(stdout(), MSG_VERBOSE, msg, args);
    va_end(args);
}

inline void msgdbg(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msgva(stdout(), MSG_DEBUG, msg, args);
    va_end(args);
}

inline void msglog(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msgva(stdout(), MSG_LOG, msg, args);
    va_end(args);
}

inline void msgwarn(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msgva(stdout(), MSG_WARNING, msg, args);
    va_end(args);
}

inline void msgerr(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msgva(stdout(), MSG_ERROR, msg, args);
    va_end(args);
}

inline void msgcrit(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msgva(stdout(), MSG_CRITICAL, msg, args);
    va_end(args);
}

