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
    static ContainerItem* containerItems;

    auto itemIds = _itemRepository->GetArsenalItemIds();
    auto totalItemIds = itemIds->size();

    // Overwrite total items to load.
    *(DWORD*)0x60BF0C = totalItemIds;

    // Build new item array.
    if (containerItems != nullptr)
    {
        delete[](containerItems);
    }
    containerItems = new ContainerItem[totalItemIds];
    unsigned char wornAmount1 = rand() % 255;
    unsigned char wornAmount2 = rand() % 255;
    unsigned char colorIndex1 = rand() % 255;
    unsigned char colorIndex2 = rand() % 255;
    unsigned char colorIndex3 = rand() % 255;
    unsigned char colorIndex4 = rand() % 255;
    for (uint32_t itemIndex = 0; itemIndex < totalItemIds; ++itemIndex)
    {
        auto containerItem = &containerItems[itemIndex];
        containerItem->ItemID = itemIds->at(itemIndex);
        containerItem->WornAmount1 = wornAmount1;
        containerItem->WornAmount2 = wornAmount2;
        containerItem->ColorIndex1 = colorIndex1;
        containerItem->ColorIndex2 = colorIndex2;
        containerItem->ColorIndex3 = colorIndex3;
        containerItem->ColorIndex4 = colorIndex4;
    }

    // Make character customization screen point to new item array.
    auto containerItemAddressBytes = (unsigned char*)&containerItems;
    unsigned char patch[] = { 0xBD, containerItemAddressBytes[0], containerItemAddressBytes[1], containerItemAddressBytes[2], containerItemAddressBytes[3] };
    Tools::memcpy_s((PVOID)(_textSectionBaseAddress + 0xFFB4C), (char*)patch, 5);
}

void __declspec(naked) HookOnArsenalScreenLoad()
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
    Tools::detour((void*)(_textSectionBaseAddress + 0xFFAC0), &HookOnArsenalScreenLoad, 6);
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

    Tools::seed_random();
    ShowConsole();
    RenameWeaponsContainerToArsenal();
    ForceCharacterCustomizationItemContainersToReloadOnNavigation();
    SuppressItemErrors();
    return TRUE;
}