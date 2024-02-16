// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocationSpawnPoint.generated.h"

UCLASS()
class TOTHEMOON_API ALocationSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ALocationSpawnPoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FString LocationName;

};
