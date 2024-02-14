// Semester 2 Christopher Boyce : TTM Project


#include "Gun.h"

#include "Damageable.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;
	
	
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
	MuzzleParticles = GetNiagaraComponentByName("MuzzleParticle");
	LightComponent= FindComponentByClass<UPointLightComponent>();

	LightComponent->SetIntensity(0.0f);
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGun::TurnOffMuzzleFlashLight()
{
	LightComponent->SetIntensity(0.0f);
}

void AGun::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRED GUN"));
	FireRay();
	if (MuzzleParticles && LaserFiring && LightComponent)
	{
		
		MuzzleParticles->ActivateSystem(true);
		UGameplayStatics::PlaySoundAtLocation(this, LaserFiring, GetActorLocation());

		LightComponent->SetIntensity(2000.0f); 
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGun::TurnOffMuzzleFlashLight, 0.05f, false);
	}
}

void AGun::FireRay()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Player controller not found"));
		return;
	}
	
	FVector CameraLocation;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
	
	FVector RayEnd = CameraLocation + CameraRotation.Vector() * 2000.0f;
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	
	ECollisionChannel CollisionChannel = ECC_Pawn;
	CollisionParams.AddIgnoredActor(PlayerController->GetPawn());
	
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, RayEnd, CollisionChannel, CollisionParams);
	
	DrawDebugLine(GetWorld(), CameraLocation, RayEnd, FColor::Red, false, 2.0f, 0, 2.0f);
	
	FVector BeamEndPoint = bHit ? HitResult.Location : RayEnd;
	
	AActor* HitActor = HitResult.GetActor();
	if (!HitActor)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Ray hit actor: %s"), *HitActor->GetName());

	if(HitActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
	{
		IDamageable* DamageableActor = Cast<IDamageable>(HitActor);
		if(DamageableActor)
		{
			DamageableActor->Execute_Damage(HitActor);
		}
	}
}

UNiagaraComponent* AGun::GetNiagaraComponentByName(FName ComponentName)
{
	TArray<UActorComponent*> Components;
	GetComponents(Components);

	for (UActorComponent* Component : Components)
	{
		UNiagaraComponent* NiagaraComponent = Cast<UNiagaraComponent>(Component);
		if (NiagaraComponent && NiagaraComponent->GetName() == ComponentName.ToString())
		{
			return NiagaraComponent;
		}
	}
	return nullptr;
}




