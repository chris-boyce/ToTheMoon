// Semester 2 Christopher Boyce : TTM Project


#include "LocationBase.h"

#include "ToTheMoon/PlayerCharacter.h"


ALocationBase::ALocationBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALocationBase::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Alive"));
	Super::BeginPlay();
}

void ALocationBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALocationBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OVERLAP"));
		PlayerOverlap.Broadcast();
		Destroy();
	}

}



