#pragma once

#include "pch.h"
#include "FacialHairAndWavyness.h"
#include "CharacterState.h"

#pragma pack(push, 1)
class Character
{
public:
	char pad_0000[4]; //0x0000
	CharacterState State; //0x0004
	char pad_0005[5]; //0x0005
	char Name[16]; //0x000A
	char pad_001A[16]; //0x001A
	float FatScalar; //0x002A
	float MuscleScalar; //0x002E -1.0 = muscular, 1.0 = weak
	float HeightScalar; //0x0032 -1.0 = tall, 1.0 = short
	float AgeScalar; //0x0036
	uint16_t SkinLightnessAmount; //0x003A
	uint16_t SkinTannedAmount; //0x003C
	uint8_t HairID; //0x003E
	char pad_003F[3]; //0x003F
	uint8_t HairHue; //0x0042
	uint8_t HairBrightness; //0x0043
	uint8_t HairGreyness; //0x0044
	char pad_0045[5]; //0x0045
	char VoiceCode[4]; //0x004A
	char pad_004E[12]; //0x004E
	float VoicePitchScalar; //0x005A
	bool IsFemale; //0x005E
	char pad_005F[1]; //0x005F
	FacialHairAndWavyness FacialHairAndWavyness; //0x0060 Even = Straight Hair, Odd = Wavy Hair
	char pad_0061[13]; //0x0061
	int16_t RightHandItemID; //0x006E
	char pad_0070[1]; //0x0070
	int16_t LeftHandItemID; //0x0071
	char pad_0073[1015]; //0x0073

};
#pragma pack(pop)