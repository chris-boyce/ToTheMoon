// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UPointLightComponent;
class USoundBase;
class UNiagaraComponent;
UCLASS()

class TOTHEMOON_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();

protected:
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;

	void TurnOffMuzzleFlashLight();
	void Fire();
	
	UNiagaraComponent* MuzzleParticles;
	
	
	UPointLightComponent* LightComponent;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* LaserFiring;

	UPROPERTY(EditAnywhere, Category="Bullet")
	TSubclassOf<AActor> Bullet;

	void FireRay();

	UNiagaraComponent* GetNiagaraComponentByName(FName ComponentName);
};
