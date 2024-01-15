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
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); // Assuming player index 0

	if (PlayerController && Other == PlayerController->GetPawn())
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap with Player Character detected"));
		PlayerHit.Broadcast(GetClass());
		Destroy();
	}
}


