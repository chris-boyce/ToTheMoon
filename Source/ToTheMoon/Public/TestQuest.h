// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "QuestBase.h"
#include "TestQuest.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOTHEMOON_API UTestQuest : public UQuestBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> QuestRewards;
};
