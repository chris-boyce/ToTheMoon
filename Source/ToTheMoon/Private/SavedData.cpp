// Semester 2 Christopher Boyce : TTM Project


#include "SavedData.h"

ASavedData* ASavedData::Instance = nullptr;

ASavedData::ASavedData()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASavedData::BeginPlay()
{
	Super::BeginPlay();
	
	Instance = this;
	
	
	
}

void ASavedData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ASavedData* ASavedData::GetInstance(UWorld* World)
{
	if (Instance == nullptr && World)
	{
		World->SpawnActor<ASavedData>();
	}
	return Instance;
}

