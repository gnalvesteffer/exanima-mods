#pragma once
namespace Tools
{
    void memcpy_s(PVOID address, char* val, int bytes);
    bool detour(void* src, void* dst, int len);
    void seed_random();
};

