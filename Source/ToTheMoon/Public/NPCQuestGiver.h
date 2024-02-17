// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "GoToQuest.h"
#include "Interactable.h"
#include "KillQuest.h"
#include "PlayerQuestComponent.h"
#include "QuestBase.h"
#include "TestQuest.h"
#include "GameFramework/Pawn.h"
#include "NPCQuestGiver.generated.h"

class UGPTComponent;
class AQuestItemBase;

UCLASS()
class TOTHEMOON_API ANPCQuestGiver : public APawn, public IInteractable
{
	GENERATED_BODY()

public:
	ANPCQuestGiver();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void Interact_Implementation() override;
	
	UPROPERTY()
	UPlayerQuestComponent* PlayerQuestComponent;
	
	UFUNCTION()
	void HandleNewQuestData(EQuestType QuestType, FQuestData QuestData);

	UPROPERTY()
	UGPTComponent* GPTComp;

	UPROPERTY()
	UQuestBase* QuestInstance;
	
	UPROPERTY()
	FLocationQuest LocationQuest;

	UPROPERTY()
	FCollectionQuest CollectionQuest;

	UPROPERTY()
	FKillQuestData KillQuest;

};
