#pragma once

enum Msg_Category
{
    MSG_VERBOSE,
    MSG_DEBUG,
    MSG_LOG,
    MSG_WARNING,
    MSG_ERROR,
    MSG_CRITICAL,
    MSG_COUNT
};

inline const char* MSG_NAMES[MSG_COUNT] = { "Verbose", "Debug", "Log", "Warning", "Error", "Critical" };

void* stdout_handle(); // standart output handle

void msg_va(void* stream, Msg_Category category, const char* msg, va_list args);

inline void msg(void* stream, Msg_Category category, const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msg_va(stream, category, msg, args);
    va_end(args);
}

inline void msg(Msg_Category category, const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msg_va(stdout_handle(), category, msg, args);
    va_end(args);
}

inline void msg_verbose(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msg_va(stdout_handle(), MSG_VERBOSE, msg, args);
    va_end(args);
}

inline void msg_debug(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msg_va(stdout_handle(), MSG_DEBUG, msg, args);
    va_end(args);
}

inline void msg_log(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msg_va(stdout_handle(), MSG_LOG, msg, args);
    va_end(args);
}

inline void msg_warning(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msg_va(stdout_handle(), MSG_WARNING, msg, args);
    va_end(args);
}

inline void msg_error(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msg_va(stdout_handle(), MSG_ERROR, msg, args);
    va_end(args);
}

inline void msg_critical(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    msg_va(stdout_handle(), MSG_CRITICAL, msg, args);
    va_end(args);
}

