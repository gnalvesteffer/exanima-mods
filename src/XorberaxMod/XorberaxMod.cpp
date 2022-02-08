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
    char8_t version = *(char8_t*)0x5BDC90;
    return version == supportedGameVersion;
}

void AddFullArsenalToPracticeArena()
{
    auto itemIds = _itemRepository->GetArsenalItemIds();
    auto totalItemIds = itemIds->size();

    // Overwrite total items to load.
    *(DWORD*)0x60BF0C = totalItemIds;

    // Build new item array.
    ContainerItem* containerItems = new ContainerItem[totalItemIds];
    for (int itemIndex = 0; itemIndex < totalItemIds; ++itemIndex)
    {
        containerItems[itemIndex].ItemID = itemIds->at(itemIndex);
    }

    // Make character customization screen point to new item array.
    unsigned char* containerItemAddressBytes = (unsigned char*)&containerItems;
    unsigned char patch[] = { 0xBD, containerItemAddressBytes[0], containerItemAddressBytes[1], containerItemAddressBytes[2], containerItemAddressBytes[3] };
    Tools::memcpy_s((PVOID)(_textSectionBaseAddress + 0xFFB4C), (char*)patch, 5);
}

void ForceCharacterCustomizationItemContainersToReloadOnNavigation()
{
    unsigned char patch[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
    Tools::memcpy_s((PVOID)(_textSectionBaseAddress + 0xFFAC0), (char*)patch, 6); // NOPs a conditional jump that checks if the weapon inventory container is already loaded, so that it reloads to grab new items.
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
    AddFullArsenalToPracticeArena();
    ForceCharacterCustomizationItemContainersToReloadOnNavigation();
    SuppressItemErrors();
    return TRUE;
}