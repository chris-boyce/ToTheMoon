// Semester 2 Christopher Boyce : TTM Project


#include "TestQuest.h"
#include "ItemSpawnPoint.h"
#include "QuestItemBase.h"
#include "SavedData.h"


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
	TSubclassOf<AQuestItemBase> SpawnActor;
	if(!ASavedData::GetInstance(WorldReference))
	{
		UE_LOG(LogTemp, Error, TEXT("InstanceDead"));
		return;
		
	}
	if(ObjectToSpawn == "Rock")
	{
		SpawnActor = ASavedData::GetInstance(WorldReference)->Rock;
	}
	else if(ObjectToSpawn == "Money")
	{
		SpawnActor = ASavedData::GetInstance(WorldReference)->Coin;
	}
	else
	{
		SpawnActor = ASavedData::GetInstance(WorldReference)->Key;
	}
	
	if(!SpawnActor)
	{
		UE_LOG(LogTemp, Error, TEXT("THIS IS DEAD"));
		return;
	}
	
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AQuestItemBase* QuestItem = WorldReference->SpawnActor<AQuestItemBase>(SpawnActor, SpawnLocation, SpawnRotation, SpawnParams);
	QuestItem->PlayerHit.AddDynamic(this, &UTestQuest::CollectedItem);
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
