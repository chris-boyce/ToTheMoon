// Semester 2 Christopher Boyce : TTM Project


#include "KillQuest.h"

#include "EngineUtils.h"
#include "ItemSpawnPoint.h"
#include "SavedData.h"
#include "Target.h"

void UKillQuest::StartQuest()
{
	Super::StartQuest();
	for (TObjectIterator<AItemSpawnPoint> Itr; Itr; ++Itr)
	{
		AItemSpawnPoint* CurrentActor = *Itr;
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
	ASavedData* FoundActor = nullptr;
	for (TActorIterator<ASavedData> It(WorldReference); It; ++It)
	{
		FoundActor = *It;
		break;
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UClass* EnemyClass = (EnemyToSpawn == "Alien") ? FoundActor->Alien : FoundActor->Pirate;
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
