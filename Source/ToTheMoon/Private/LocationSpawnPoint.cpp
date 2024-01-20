// Semester 2 Christopher Boyce : TTM Project


#include "LocationSpawnPoint.h"

// Sets default values
ALocationSpawnPoint::ALocationSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALocationSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALocationSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

