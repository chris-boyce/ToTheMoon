// Semester 2 Christopher Boyce : TTM Project


#include "GoToQuest.h"

#include "ItemSpawnPoint.h"
#include "LocationBase.h"
#include "LocationSpawnPoint.h"
#include "SavedData.h"

void UGoToQuest::StartQuest()
{
	UE_LOG(LogTemp, Warning, TEXT("GoToHasStarted"));
	Super::StartQuest();
	for (TObjectIterator<ALocationSpawnPoint> Itr; Itr; ++Itr)
	{
		ALocationSpawnPoint* CurrentActor = *Itr;
		FString LocationName = CurrentActor->LocationName;
		
		if (LocationName == SpawnPointName)
		{
			SpawnPoint = CurrentActor->GetActorLocation();
			SpawnLocationCollider(SpawnPoint);
			UE_LOG(LogTemp, Warning, TEXT("Location Found"));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Run Spawn"));
	
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

void UGoToQuest::SpawnLocationCollider(FVector SpawnLocation)
{
	FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ALocationBase* LocationBase = WorldReference->SpawnActor<ALocationBase>(ASavedData::GetInstance(WorldReference)->SpawnPoint, SpawnLocation, SpawnRotation, SpawnParams);
	LocationBase->PlayerOverlap.AddDynamic(this, &UGoToQuest::CompleteStep);
	
	UE_LOG(LogTemp, Warning, TEXT("WE HAVE FINSHED THIS CODE Spawned"));
}

void UGoToQuest::InitQuestVariables(const FLocationQuest& Parameters)
{
	Super::InitQuestVariables(Parameters);
	SpawnPointName = Parameters.LocationName;
	UE_LOG(LogTemp, Warning, TEXT("GOTO InitQuest Started"));
	StartQuest();
}
