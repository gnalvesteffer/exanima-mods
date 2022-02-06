#include "pch.h"
#include "Tools.h"

void Tools::memcpy_s(PVOID address, char* val, int bytes)
{
    DWORD d, ds;
    VirtualProtect(address, bytes, PAGE_EXECUTE_READWRITE, &d);
    memcpy(address, val, bytes);
    VirtualProtect(address, bytes, d, &ds);
}