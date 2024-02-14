// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS()
class TOTHEMOON_API ATarget : public AActor, public IDamageable
{
	GENERATED_BODY()
	
public:	
	ATarget();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Damage_Implementation() override;

};
