// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimSequence.h"
#include "Chest.generated.h"

UCLASS()
class TOTHEMOON_API AChest : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AChest();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* OpenAnimation;

	//Called from when the player interacts with the Chest
	UFUNCTION()
	virtual void Interact_Implementation() override;

};
