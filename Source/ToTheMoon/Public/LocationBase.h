// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocationBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOverlapPlayer);
UCLASS(Abstract)
class TOTHEMOON_API ALocationBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocationBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FOverlapPlayer PlayerOverlap;

};