// Semester 2 Christopher Boyce : TTM Project


#include "LocationBase.h"

// Sets default values
ALocationBase::ALocationBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALocationBase::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Alive"));
	Super::BeginPlay();
	
}

// Called every frame
void ALocationBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALocationBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP"));
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayerOverlap.Broadcast();
	Destroy();
}


