#include "pch.h"
#include "file.h"
#include "str.h"

s32 FILE_ACCESS_READ    = GENERIC_READ;
s32 FILE_ACCESS_WRITE   = GENERIC_WRITE;
s32 FILE_ACCESS_EXEC    = GENERIC_EXECUTE;

s32 FILE_CREATE_NEW     = CREATE_NEW;
s32 FILE_OPEN_EXISTING  = OPEN_EXISTING;

hfile open_file(const char* fpath, s32 open, s32 access)
{
    wchar_t wfpath[512];
    utf8_to_utf16(fpath, wfpath);
    return CreateFileW(wfpath, access, 0, NULL, open, FILE_ATTRIBUTE_NORMAL, NULL);
}

bool close_file(hfile handle)
{
    return CloseHandle(handle);
}

bool read_file_sync(hfile handle, u8* buffer, u64 size, u64* nbytes)
{
    return ReadFile(handle, buffer, (DWORD)size, (LPDWORD)nbytes, NULL);
}

bool write_file_sync(hfile handle, u8* buffer, u64 size, u64* nbytes)
{
    return WriteFile(handle, buffer, (DWORD)size, (LPDWORD)nbytes, NULL);
}
