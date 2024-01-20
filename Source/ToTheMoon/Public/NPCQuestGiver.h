// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Pawn.h"
#include "NPCQuestGiver.generated.h"

UCLASS()
class TOTHEMOON_API ANPCQuestGiver : public APawn, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANPCQuestGiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void Interact_Implementation() override;

};
