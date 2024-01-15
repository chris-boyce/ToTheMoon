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
	TSubclassOf<AQuestItemBase> QuestItem;
	
	UPROPERTY(EditAnywhere)
	int ItemCollectionAmount;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCollectionQuest QuestItemList;

	virtual void StartQuest() override;

	UPROPERTY()
	UWorld* World;

	UFUNCTION()
	void SpawnItem(int SpawnPoint);

	UFUNCTION()
	void CollectedItem(UClass* ObjectClass);

	UFUNCTION()
	void HandleCorrectItem();

	UPROPERTY()
	int AmountCollected = 0;

	
};
