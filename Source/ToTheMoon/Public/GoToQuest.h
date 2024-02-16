// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "QuestBase.h"
#include "GoToQuest.generated.h"

USTRUCT(BlueprintType)
struct FLocationQuest
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString LocationName;
	
};

class ALocationBase;
UCLASS(Blueprintable)
class TOTHEMOON_API UGoToQuest : public UQuestBase
{
	GENERATED_BODY()
	virtual void StartQuest() override;
	virtual void CompleteStep() override;
public:
	UFUNCTION()
	void LocationCollision();
	
	UFUNCTION()
	void SpawnLocationCollider(FVector Location);

	UPROPERTY(EditAnywhere)
	TSubclassOf<ALocationBase> LocationBaseClass = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnPoint;

	UPROPERTY()
	FString SpawnPointName;
	
	void InitQuestVariables(const FLocationQuest& Parameters) override;
};
