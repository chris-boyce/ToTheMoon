// Semester 2 Christopher Boyce : TTM Project


#include "Target.h"


ATarget::ATarget()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget::Damage_Implementation()
{
	IDamageable::Damage_Implementation();
	OnDeath.Broadcast();
	Destroy();
}

