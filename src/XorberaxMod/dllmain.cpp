// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "XorberaxMod.h"

DWORD __stdcall ModThread(void* pParam)
{
    (new XorberaxMod())->Start();
    return 0;
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, ModThread, nullptr, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

