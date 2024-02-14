// Semester 2 Christopher Boyce : TTM Project


#include "QuestItemBase.h"

#include "Kismet/GameplayStatics.h"


AQuestItemBase::AQuestItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

}


void AQuestItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AQuestItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuestItemBase::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	
}

void AQuestItemBase::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
	PlayerHit.Broadcast(GetClass());
	Destroy();
}


