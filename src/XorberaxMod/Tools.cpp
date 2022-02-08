#include "pch.h"
#include "Tools.h"

void Tools::memcpy_s(PVOID address, char* val, int bytes)
{
    DWORD d, ds;
    VirtualProtect(address, bytes, PAGE_EXECUTE_READWRITE, &d);
    memcpy(address, val, bytes);
    VirtualProtect(address, bytes, d, &ds);
}

// Adapted from https://guidedhacking.com/threads/how-to-hook-functions-code-detouring-guide.14185/
bool Tools::detour(void* src, void* dst, int len)
{
    if (len < 5) return false;

    DWORD curProtection;
    VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

    memset(src, 0x90, len);

    uintptr_t relativeAddress = ((uintptr_t)dst - (uintptr_t)src) - 5;

    *(BYTE*)src = 0xE9;
    *(uintptr_t*)((uintptr_t)src + 1) = relativeAddress;

    DWORD temp;
    VirtualProtect(src, len, curProtection, &temp);

    return true;
}