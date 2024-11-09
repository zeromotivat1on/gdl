#pragma once

#define SID(str) sidgen(str)

typedef u64 sid;

// TODO: implement own hash table.
inline std::unordered_map<sid, const char*> gSidTable;

inline sid sidhash(const char* str)
{
    return hashfnv(str);
}
    
inline sid sidgen(const char* str)
{
    sid hash = sidhash(str);
    gSidTable.try_emplace(hash, str);
    return hash;
}

inline const char* sidstr(sid n)
{
    return gSidTable.at(n);
}

inline bool sidunique(sid n)
{
    return gSidTable.find(n) == gSidTable.end();
}

inline bool sidunique(const char* str)
{
    return gSidTable.find(sidhash(str)) == gSidTable.end();
}
