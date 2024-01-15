// Semester 2 Christopher Boyce : TTM Project


#include "TestQuest.h"

#include "ItemSpawnPoint.h"

void UTestQuest::StartQuest()
{
	Super::StartQuest();
	World = GetWorld();
	//Create Spawn List : Gets all spawn Location transforms and makes a list.
	for (TObjectIterator<AItemSpawnPoint> Itr; Itr; ++Itr)
	{
		AItemSpawnPoint* CurrentActor = *Itr;
		FTransform ActorTransform = CurrentActor->GetActorTransform();
		FVector ActorLocation = ActorTransform.GetLocation();
		SpawnPoints.Add(ActorLocation);
	}
	//Calls Spawn Function and gives a random Index to spawn it at.
	for (int32 Index = 0; Index < QuestItemList.ItemCollectionAmount; ++Index)
	{
		SpawnItem(FMath::RandRange(0, SpawnPoints.Num() - 1));
	}
	 
}

void UTestQuest::SpawnItem(int SpawnPoint)
{
	
	//Spawns Object at location and adds a call the base of Quest for when it is collected
	FVector SpawnLocation = SpawnPoints[SpawnPoint];
	FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	
	AQuestItemBase* SpawnedItem = World->SpawnActor<AQuestItemBase>(QuestItemList.QuestItem, SpawnLocation , SpawnRotation);
	SpawnedItem->PlayerHit.AddDynamic(this, &UTestQuest::CollectedItem);
}

void UTestQuest::CollectedItem(UClass* ObjectClass)
{
	//When Item Collected it checks if it is a The Quest Item they are looking for
	if(ObjectClass == QuestItemList.QuestItem)
	{
		HandleCorrectItem();
	}
}

void UTestQuest::HandleCorrectItem()
{
	//If its correct it will add it to the total and compare it to the Quest
	AmountCollected++;
	if(AmountCollected == QuestItemList.ItemCollectionAmount)
	{
		//If they have got them all it will return the Step has been completed
		//TODO : Add Multi Step
		CompleteStep();
	}
}
