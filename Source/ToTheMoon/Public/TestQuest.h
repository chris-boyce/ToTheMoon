// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "QuestBase.h"
#include "QuestItemBase.h"
#include "TestQuest.generated.h"

//Collection Quest Needed Variables
USTRUCT(BlueprintType)
struct FCollectionQuest
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int ItemCollectionAmount;

	UPROPERTY(EditAnywhere)
	FString ItemName;
	
};

UCLASS(Blueprintable)
class TOTHEMOON_API UTestQuest : public UQuestBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> QuestRewards;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> SpawnPoints;

	UPROPERTY()
	FString ObjectToSpawn;
	
	virtual void StartQuest() override;
	
	UFUNCTION()
	void SpawnItem(int SpawnPoint);

	UFUNCTION()
	void CollectedItem(UClass* ObjectClass);

	UFUNCTION()
	void HandleCorrectItem();

	UPROPERTY()
	int TotalCollected = 0;

	UPROPERTY()
	int AmountCollected = 0;

	

	virtual void InitQuestVariables(const FCollectionQuest& Parameters) override;

	
};
