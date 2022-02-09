#include "pch.h"
#include "Tools.h"
#include "ItemRepository.h"
#include "ContainerItem.h"
#include "XorberaxMod.h"

const auto _textSectionBaseAddress = (DWORD)0x401000;
const auto _itemRepository = new ItemRepository();

bool IsGameVersionSupported()
{
    static const auto supportedGameVersion = *u8"V 0.8.3p";
    auto version = *(char8_t*)0x5BDC90;
    return version == supportedGameVersion;
}

void ShowConsole()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

void RenameWeaponsContainerToArsenal()
{
    static const auto arsenalString = "ARSENAL";
    Tools::memcpy_s((PVOID)0x0500BDC, (char*)arsenalString, 16);
}

void AddFullArsenalToPracticeArena()
{
    auto itemIds = _itemRepository->GetArsenalItemIds();
    auto totalItemIds = itemIds->size();

    // Overwrite total items to load.
    *(DWORD*)0x60BF0C = totalItemIds;

    // Build new item array.
    ContainerItem* containerItems = new ContainerItem[totalItemIds];
    for (uint32_t itemIndex = 0; itemIndex < totalItemIds; ++itemIndex)
    {
        auto containerItem = &containerItems[itemIndex];
        containerItem->ItemID = itemIds->at(itemIndex);
        containerItem->ColorIndex = rand() % 255;
        containerItem->N00000060 = rand() % 255;
        containerItem->N00000066 = rand() % 255;
        containerItem->N00000072 = rand() % 255;
        containerItem->N00000067 = rand() % 255;
        containerItem->N00000061 = rand() % 255;
        containerItem->N00000069 = rand() % 255;
        containerItem->N00000075 = rand() % 255;
        containerItem->N0000006A = rand() % 255;
        containerItem->N00000062 = rand() % 255;
        containerItem->N0000006C = rand() % 255;
        containerItem->N00000078 = rand() % 255;
        containerItem->N00000063 = rand() % 255;
        containerItem->N0000006F = rand() % 255;
        containerItem->N00000064 = rand() % 255;
    }

    // Make character customization screen point to new item array.
    auto containerItemAddressBytes = (unsigned char*)&containerItems;
    unsigned char patch[] = { 0xBD, containerItemAddressBytes[0], containerItemAddressBytes[1], containerItemAddressBytes[2], containerItemAddressBytes[3] };
    Tools::memcpy_s((PVOID)(_textSectionBaseAddress + 0xFFB4C), (char*)patch, 5);
}

void __declspec(naked) OnArsenalScreenLoad()
{
    static const DWORD jumpBackAddress = _textSectionBaseAddress + 0xFFAC6;
    __asm {
        call AddFullArsenalToPracticeArena
        jmp [jumpBackAddress]
    }
}

void ForceCharacterCustomizationItemContainersToReloadOnNavigation()
{
    // Replaces a conditional jump that checks if the weapon inventory container is already loaded, so that it reloads to grab new items.
    Tools::detour((void*)(_textSectionBaseAddress + 0xFFAC0), &OnArsenalScreenLoad, 6);
}

void SuppressItemErrors()
{
    unsigned char patch[] = { 0xC3 };
    Tools::memcpy_s((PVOID)(_textSectionBaseAddress + 0x177794), (char*)patch, 1);
}

bool XorberaxMod::Start()
{
    if (!IsGameVersionSupported())
    {
        MessageBox(NULL, L"XorberaxMod requires Exanima V 0.8.3p.", L"Game version not supported.", MB_OK);
        return FALSE;
    }
    ShowConsole();
    RenameWeaponsContainerToArsenal();
    ForceCharacterCustomizationItemContainersToReloadOnNavigation();
    SuppressItemErrors();
    return TRUE;
}