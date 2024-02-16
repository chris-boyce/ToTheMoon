// Semester 2 Christopher Boyce : TTM Project


#include "GoToQuest.h"

#include "ItemSpawnPoint.h"
#include "LocationBase.h"
#include "LocationSpawnPoint.h"

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

	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Quests/BP_Location.BP_Location")));

	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	if (!SpawnActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	UClass* SpawnClass = SpawnActor->StaticClass();
	if (SpawnClass == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	WorldReference->SpawnActor<AActor>(GeneratedBP->GeneratedClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	UE_LOG(LogTemp, Warning, TEXT("WE HAVE FINSHED THIS CODE Spawned"));
}

void UGoToQuest::InitQuestVariables(const FLocationQuest& Parameters)
{
	Super::InitQuestVariables(Parameters);
	SpawnPointName = Parameters.LocationName;
	UE_LOG(LogTemp, Warning, TEXT("GOTO InitQuest Started"));
	StartQuest();
}
