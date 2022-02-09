#pragma once

#include "pch.h"

#pragma pack(push, 1)
class ContainerItem
{
public:
	uint32_t ItemID; //0x0000
	uint8_t N00000060; //0x0004
	uint8_t N00000066; //0x0005
	uint8_t N00000072; //0x0006
	uint8_t N00000067; //0x0007
	uint8_t N00000061; //0x0008
	uint8_t WornAmount1; //0x0009
	uint8_t WornAmount2; //0x000A
	uint8_t N0000006A; //0x000B
	uint8_t N00000062; //0x000C
	uint8_t N0000006C; //0x000D
	uint8_t N00000078; //0x000E
	uint8_t ColorIndex1; //0x000F
	uint8_t ColorIndex2; //0x0010
	uint8_t ColorIndex3; //0x0011
	uint8_t ColorIndex4; //0x0012
}; //Size: 0x0013
#pragma pack(pop)