// Semester 2 Christopher Boyce : TTM Project


#include "KillQuest.h"

#include "EnemySpawnPoint.h"
#include "EngineUtils.h"
#include "ItemSpawnPoint.h"
#include "SavedData.h"
#include "Target.h"

void UKillQuest::StartQuest()
{
	Super::StartQuest();
	for (TObjectIterator<AEnemySpawnPoint> Itr; Itr; ++Itr)
	{
		AEnemySpawnPoint* CurrentActor = *Itr;
		FTransform ActorTransform = CurrentActor->GetActorTransform();
		FVector ActorLocation = ActorTransform.GetLocation();
		SpawnPoints.Add(ActorLocation);
	}
	for (int32 Index = 0; Index < AmountToKill; ++Index)
	{
		SpawnEnemy(FMath::RandRange(0, SpawnPoints.Num() - 1));
	}
}

void UKillQuest::SpawnEnemy(int SpawnPoint)
{
	FVector SpawnLocation = SpawnPoints[SpawnPoint];
	FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TSubclassOf<ATarget> EnemyClass = (EnemyToSpawn == "Alien") ? ASavedData::GetInstance(WorldReference)->Alien : ASavedData::GetInstance(WorldReference)->Pirate;
	if(!ASavedData::GetInstance(WorldReference))
	{
		UE_LOG(LogTemp, Error, TEXT("Wolrd is Dead"));
		return;
		
	}
	if(!EnemyClass)
	{
		UE_LOG(LogTemp, Error, TEXT("THIS IS DEAD 2"));
		return;
	}
	ATarget* Enemy = WorldReference->SpawnActor<ATarget>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParams);
	Enemy->OnDeath.AddDynamic(this, &UKillQuest::HandleEnemyDeath);
}

void UKillQuest::HandleEnemyDeath()
{
	TotalKilled++;
	if(AmountToKill == TotalKilled)
	{
		CompleteStep();
	}
}

void UKillQuest::InitQuestVariables(const FKillQuestData& Parameters)
{
	Super::InitQuestVariables(Parameters);
	EnemyToSpawn = Parameters.EnemyToKill;
	AmountToKill = Parameters.AmountToKill;
	StartQuest();
}
