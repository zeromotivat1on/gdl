#include "pch.h"
#include "file.h"
#include "str.h"

s32 FILE_ACCESS_READ    = GENERIC_READ;
s32 FILE_ACCESS_WRITE   = GENERIC_WRITE;
s32 FILE_ACCESS_EXEC    = GENERIC_EXECUTE;

s32 FILE_CREATE_NEW     = CREATE_NEW;
s32 FILE_OPEN_EXISTING  = OPEN_EXISTING;

fhandle fstart(const char* fpath, s32 access, s32 start)
{
    wchar_t wfpath[512];
    utf8to16(fpath, wfpath);
    return CreateFileW(wfpath, access, 0, NULL, start, FILE_ATTRIBUTE_NORMAL, NULL);
}

bool fstop(fhandle handle)
{
    return CloseHandle(handle);
}

bool freadsync(fhandle handle, u8* buffer, u64 size, u64* nbytes)
{
    return ReadFile(handle, buffer, size, (LPDWORD)nbytes, NULL);
}

bool fwritesync(fhandle handle, u8* buffer, u64 size, u64* nbytes)
{
    return WriteFile(handle, buffer, size, (LPDWORD)nbytes, NULL);
}
