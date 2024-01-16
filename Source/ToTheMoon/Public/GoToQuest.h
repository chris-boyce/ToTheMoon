// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "QuestBase.h"
#include "GoToQuest.generated.h"

UCLASS()
class TOTHEMOON_API UGoToQuest : public UQuestBase
{
	GENERATED_BODY()
	virtual void StartQuest() override;
	virtual void CompleteStep() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Locations;

	UFUNCTION()
	void LocationCollision();
	
	UFUNCTION()
	void SpawnLocationCollider(int LocationInt);
};
