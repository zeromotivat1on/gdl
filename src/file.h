#pragma once

// -----
// Types
// -----

extern s32 FILE_ACCESS_READ;    // file can be read from
extern s32 FILE_ACCESS_WRITE;   // file can be written to
extern s32 FILE_ACCESS_EXEC;    // file can be executed

extern s32 FILE_CREATE_NEW;     // create new file or fail
extern s32 FILE_OPEN_EXISTING;  // open existing file or fail

typedef void*   hfile; // file handle

// ----
// Core
// ----

hfile   file_open(const char* fpath, s32 open, s32 access);
bool    file_close(hfile handle);

bool    file_read_sync(hfile handle, u8* buffer, u64 size, u64* nbytes);
bool    file_write_sync(hfile handle, u8* buffer, u64 size, u64* nbytes);

// -----
// Extra
// -----

// Convenient wrappers to read/write from/to existing file.

inline bool file_read_sync(const char* fpath, u8* buffer, u64 size, u64* nbytes)
{
    if (hfile handle = file_open(fpath, FILE_OPEN_EXISTING, FILE_ACCESS_READ))
    {
        const bool res = file_read_sync(handle, buffer, size, nbytes);
        file_close(handle);
        return res;
    }

    return false;
}

inline bool file_write_sync(const char* fpath, u8* buffer, u64 size, u64* nbytes)
{
    if (hfile handle = file_open(fpath, FILE_OPEN_EXISTING, FILE_ACCESS_WRITE))
    {
        const bool res = file_write_sync(handle, buffer, size, nbytes);
        file_close(handle);
        return res;
    }

    return false;
}
