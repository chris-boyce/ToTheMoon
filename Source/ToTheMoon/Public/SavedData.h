// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SavedData.generated.h"

UCLASS()
class TOTHEMOON_API ASavedData : public AActor
{
	GENERATED_BODY()
	
public:	
	ASavedData();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="SavedData")
	TSubclassOf<AActor> Pirate;

	UPROPERTY(EditAnywhere, Category="SavedData")
	TSubclassOf<AActor> Alien;
	

};
