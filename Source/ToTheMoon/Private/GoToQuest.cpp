// Semester 2 Christopher Boyce : TTM Project


#include "GoToQuest.h"

#include "LocationBase.h"
#include "LocationSpawnPoint.h"

void UGoToQuest::StartQuest()
{
	Super::StartQuest();
	World = GetWorld();
	//Create Spawn List : Gets all spawn Location transforms and makes a list.
	for (TObjectIterator<ALocationSpawnPoint> Itr; Itr; ++Itr)
	{
		ALocationSpawnPoint* CurrentActor = *Itr;
		FTransform ActorTransform = CurrentActor->GetActorTransform();
		FVector ActorLocation = ActorTransform.GetLocation();
		SpawnPoints.Add(ActorLocation);
	}
	
	//Calls Spawn Function and gives a random Index to spawn it at.
	
	SpawnLocationCollider(FMath::RandRange(0, SpawnPoints.Num() - 1));
	
}

void UGoToQuest::CompleteStep()
{

	Super::CompleteStep();
}

void UGoToQuest::LocationCollision()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Detected"));
	CompleteStep();
}

void UGoToQuest::SpawnLocationCollider(int LocationInt)
{
	FVector SpawnLocation = SpawnPoints[LocationInt];
	FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	
	ALocationBase* SpawnedItem = World->SpawnActor<ALocationBase>(Location, SpawnLocation , SpawnRotation);
	SpawnedItem->PlayerOverlap.AddDynamic(this, &UGoToQuest::LocationCollision);
}
