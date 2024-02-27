// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "LocationBase.h"
#include "QuestItemBase.h"
#include "Target.h"
#include "GameFramework/Actor.h"
#include "SavedData.generated.h"

UCLASS()
class TOTHEMOON_API ASavedData : public AActor
{
	GENERATED_BODY()
	
public:	
	ASavedData();

protected:
	virtual void BeginPlay() override;
private:
	static ASavedData* Instance;

public:	
	virtual void Tick(float DeltaTime) override;

	static ASavedData* GetInstance(UWorld* World);

	UPROPERTY(EditAnywhere, Category="SavedData")
	TSubclassOf<ATarget> Pirate;

	UPROPERTY(EditAnywhere, Category="SavedData")
	TSubclassOf<ATarget> Alien;

	UPROPERTY(EditAnywhere, Category="SavedData")
	TSubclassOf<AQuestItemBase> Coin;

	UPROPERTY(EditAnywhere, Category="SavedData")
	TSubclassOf<AQuestItemBase> Rock;
	
	UPROPERTY(EditAnywhere, Category="SavedData")
	TSubclassOf<AQuestItemBase> Key;

	UPROPERTY(EditAnywhere, Category="SavedData")
	TSubclassOf<ALocationBase> SpawnPoint;

	UPROPERTY(EditAnywhere, Category="WorldData")
	FString Name = "Name";
	UPROPERTY(EditAnywhere, Category="WorldData")
	FString System = "System";
	UPROPERTY(EditAnywhere, Category="WorldData")
	FString Classification = "Classic";
	
	UPROPERTY(EditAnywhere, Category="WorldData")
	FString Date = "01/01/2001";
	UPROPERTY(EditAnywhere, Category="WorldData")
	FString Time = "12:00";
	

};
