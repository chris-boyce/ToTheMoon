// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestItemBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitPlayer, UClass*, ObjectClass);

UCLASS(Abstract)
class TOTHEMOON_API AQuestItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuestItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
	FHitPlayer PlayerHit;

};
