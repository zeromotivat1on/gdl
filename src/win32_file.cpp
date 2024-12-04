#include "pch.h"
#include "file.h"
#include "str.h"

s32 FILE_ACCESS_READ    = GENERIC_READ;
s32 FILE_ACCESS_WRITE   = GENERIC_WRITE;
s32 FILE_ACCESS_EXEC    = GENERIC_EXECUTE;

s32 FILE_CREATE_NEW     = CREATE_NEW;
s32 FILE_OPEN_EXISTING  = OPEN_EXISTING;

file_handle open_file(const char* path, s32 open, s32 access)
{
    wchar_t wide_path[512];
    utf8_to_utf16(path, wide_path);
    return CreateFileW(wide_path, access, 0, NULL, open, FILE_ATTRIBUTE_NORMAL, NULL);
}

bool close_file(file_handle handle)
{
    return CloseHandle(handle);
}

bool read_file_sync(file_handle handle, u8* buffer, u64 size, u64* bytes_read)
{
    return ReadFile(handle, buffer, (DWORD)size, (LPDWORD)bytes_read, NULL);
}

bool write_file_sync(file_handle handle, u8* buffer, u64 size, u64* bytes_read)
{
    return WriteFile(handle, buffer, (DWORD)size, (LPDWORD)bytes_read, NULL);
}
