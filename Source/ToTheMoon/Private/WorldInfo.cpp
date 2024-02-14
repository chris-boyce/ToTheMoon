// Semester 2 Christopher Boyce : TTM Project


#include "WorldInfo.h"

// Sets default values
AWorldInfo::AWorldInfo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldInfo::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWorldInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

