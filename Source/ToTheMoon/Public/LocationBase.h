// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocationBase.generated.h"
class UPaperSpriteComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOverlapPlayer);
UCLASS()
class TOTHEMOON_API ALocationBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ALocationBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FOverlapPlayer PlayerOverlap;

	UPROPERTY()
	UPaperSpriteComponent* PaperSpriteComponent;

	
	

	

};
