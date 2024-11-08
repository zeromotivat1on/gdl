#pragma once

// -----
// Types
// -----

extern s32 FILE_ACCESS_READ;    // file can be read from
extern s32 FILE_ACCESS_WRITE;   // file can be written to
extern s32 FILE_ACCESS_EXEC;    // file can be executed

extern s32 FILE_CREATE_NEW;     // create new file or fail
extern s32 FILE_OPEN_EXISTING;  // open existing file or fail

typedef void*   fhandle; // file handle

// ----
// Core
// ----

fhandle fstart(const char* fpath, s32 access, s32 start);
bool    fstop(fhandle handle);

bool    freadsync(fhandle handle, u8* buffer, u64 size, u64* nbytes);
bool    fwritesync(fhandle handle, u8* buffer, u64 size, u64* nbytes);

// -----
// Extra
// -----

// Convenient wrappers to read/write from/to existing file.

inline bool freadsync(const char* fpath, u8* buffer, u64 size, u64* nbytes)
{
    if (fhandle handle = fstart(fpath, FILE_ACCESS_READ, FILE_OPEN_EXISTING))
    {
        const bool res = freadsync(handle, buffer, size, nbytes);
        fstop(handle);
        return res;
    }

    return false;
}

inline bool fwritesync(const char* fpath, u8* buffer, u64 size, u64* nbytes)
{
    if (fhandle handle = fstart(fpath, FILE_ACCESS_WRITE, FILE_OPEN_EXISTING))
    {
        const bool res = fwritesync(handle, buffer, size, nbytes);
        fstop(handle);
        return res;
    }

    return false;
}
