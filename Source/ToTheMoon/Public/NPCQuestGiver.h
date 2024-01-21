// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "PlayerQuestComponent.h"
#include "GameFramework/Pawn.h"
#include "NPCQuestGiver.generated.h"

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

	UFUNCTION()
	void QuestGive();

	UPROPERTY()
	UPlayerQuestComponent* PlayerQuestComponent;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AQuestItemBase>> QuestItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="NPC|Quests")
	TArray<TSubclassOf<UQuestBase>> QuestTypes;

};
