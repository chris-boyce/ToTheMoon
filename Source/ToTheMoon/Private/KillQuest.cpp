// Semester 2 Christopher Boyce : TTM Project


#include "KillQuest.h"
#include "ItemSpawnPoint.h"
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
	UObject* SpawnActor;
	SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Quests/BP_Target.BP_Target")));
	if (!SpawnActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}
	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	UClass* SpawnClass = SpawnActor->StaticClass();
	if (SpawnClass == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
		return;
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ATarget* Enemy = WorldReference->SpawnActor<ATarget>(GeneratedBP->GeneratedClass, SpawnLocation, SpawnRotation, SpawnParams);
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
