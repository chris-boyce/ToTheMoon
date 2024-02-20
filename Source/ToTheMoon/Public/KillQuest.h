// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "QuestBase.h"
#include "KillQuest.generated.h"

//Collection Quest Needed Variables
USTRUCT(BlueprintType)
struct FKillQuestData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int AmountToKill;

	UPROPERTY(EditAnywhere)
	FString EnemyToKill;
};


UCLASS(Blueprintable)
class TOTHEMOON_API UKillQuest : public UQuestBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> SpawnPoints;

	UPROPERTY()
	FString EnemyToSpawn;
	
	virtual void StartQuest() override;

	UFUNCTION()
	void SpawnEnemy(int SpawnPoint);

	UFUNCTION()
	void HandleEnemyDeath();

	UPROPERTY()
	int TotalKilled = 0;

	UPROPERTY()
	int AmountToKill = 0;

	virtual void InitQuestVariables(const FKillQuestData& Parameters) override;
	
};
