#pragma once

#include <unordered_map>

#define SID(str) sidgen(str)

typedef u64 sid;

// TODO: implement own hash table.
inline std::unordered_map<sid, const char*> sidtable;

inline sid sidhash(const char* str)
{
    return hashfnv(str);
}
    
inline sid sidgen(const char* str)
{
    sid hash = sidhash(str);
    sidtable.try_emplace(hash, str);
    return hash;
}

inline const char* sidstr(sid n)
{
    return sidtable.at(n);
}

inline bool sidunique(sid n)
{
    return sidtable.find(n) == sidtable.end();
}

inline bool sidunique(const char* str)
{
    return sidtable.find(sidhash(str)) == sidtable.end();
}
