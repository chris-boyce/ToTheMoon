// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"

struct FNPCData
{
	FString Name;
	FString IntroString;
	int32 Level;
	FString Lore;
};

class TOTHEMOON_API NPCReader
{
public:
	NPCReader();
	FNPCData ReadJSONFile(const FString& FileName);
	~NPCReader();
};
