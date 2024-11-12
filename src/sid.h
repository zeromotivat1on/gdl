#pragma once

#include <unordered_map>

#define SID(str) sid_gen(str)

typedef u64 sid;

// TODO: implement own hash table.
inline std::unordered_map<sid, const char*> SID_TABLE;

inline sid sid_hash(const char* str)
{
    return hash_fnv(str);
}
    
inline sid sid_gen(const char* str)
{
    sid hash = sid_hash(str);
    SID_TABLE.try_emplace(hash, str);
    return hash;
}

inline const char* sid_str(sid n)
{
    return SID_TABLE.at(n);
}

inline bool sid_unique(sid n)
{
    return SID_TABLE.find(n) == SID_TABLE.end();
}

inline bool sid_unique(const char* str)
{
    return SID_TABLE.find(sid_hash(str)) == SID_TABLE.end();
}
