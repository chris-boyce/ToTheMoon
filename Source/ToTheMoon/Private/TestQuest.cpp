// Semester 2 Christopher Boyce : TTM Project


#include "TestQuest.h"
#include "ItemSpawnPoint.h"
#include "QuestItemBase.h"


void UTestQuest::StartQuest()
{
	Super::StartQuest();
	for (TObjectIterator<AItemSpawnPoint> Itr; Itr; ++Itr)
	{
		AItemSpawnPoint* CurrentActor = *Itr;
		FTransform ActorTransform = CurrentActor->GetActorTransform();
		FVector ActorLocation = ActorTransform.GetLocation();
		SpawnPoints.Add(ActorLocation);
	}
	for (int32 Index = 0; Index < AmountCollected; ++Index)
	{
		SpawnItem(FMath::RandRange(0, SpawnPoints.Num() - 1));
	}
	 
}

void UTestQuest::SpawnItem(int SpawnPoint)
{
	//Spawns Object at location and adds a call the base of Quest for when it is collected
	FVector SpawnLocation = SpawnPoints[SpawnPoint];
	FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	UObject* SpawnActor;
	if(ObjectToSpawn == "Rock")
	{
		SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Quests/QuestItems/QuestItemRock.QuestItemRock")));
	}
	else if(ObjectToSpawn == "Money")
	{
		SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Quests/QuestItems/QuestItemCoin.QuestItemCoin")));
	}
	else
	{
		SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Quests/QuestItems/QuestItemKey.QuestItemKey")));
	}
	
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
	AQuestItemBase* LocationBase = WorldReference->SpawnActor<AQuestItemBase>(GeneratedBP->GeneratedClass, SpawnLocation, SpawnRotation, SpawnParams);
	LocationBase->PlayerHit.AddDynamic(this, &UTestQuest::CollectedItem);
}

void UTestQuest::CollectedItem(UClass* ObjectClass)
{
	HandleCorrectItem();
}

void UTestQuest::HandleCorrectItem()
{
	TotalCollected++;
	if(AmountCollected == TotalCollected)
	{
		CompleteStep();
	}
}

void UTestQuest::InitQuestVariables(const FCollectionQuest& Parameters)
{
	Super::InitQuestVariables(Parameters);
	ObjectToSpawn = Parameters.ItemName;
	AmountCollected = Parameters.ItemCollectionAmount;
	StartQuest();
}
