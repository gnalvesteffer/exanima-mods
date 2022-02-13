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
    char pad_0005[3]; //0x0005
    char Name[16]; //0x0008
    char pad_0018[16]; //0x0018
    float FatScalar; //0x0028
    float MuscleScalar; //0x002C -1.0 = muscular, 1.0 = weak
    float HeightScalar; //0x0030 -1.0 = tall, 1.0 = short
    float AgeScalar; //0x0034
    uint16_t SkinLightnessAmount; //0x0038
    uint16_t SkinTannedAmount; //0x003A
    uint8_t HairID; //0x003C
    char pad_003D[3]; //0x003D
    uint8_t HairHue; //0x0040
    uint8_t HairBrightness; //0x0041
    uint8_t HairGreyness; //0x0042
    char pad_0043[5]; //0x0043
    char VoiceCode[4]; //0x0048
    char pad_004C[12]; //0x004C
    float VoicePitchScalar; //0x0058
    bool IsFemale; //0x005C
    char pad_005D[1]; //0x005D
    FacialHairAndWavyness FacialHairAndWavyness; //0x005E Even = Straight Hair, Odd = Wavy Hair
    char pad_005F[13]; //0x005F
    int16_t RightHandItemID; //0x006C
    char pad_006E[1]; //0x006E
    int16_t LeftHandItemID; //0x006F
    char pad_0071[1015]; //0x0071
};
#pragma pack(pop)