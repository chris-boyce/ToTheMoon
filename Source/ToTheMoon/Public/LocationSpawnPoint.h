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
	// Sets default values for this actor's properties
	ALocationSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
