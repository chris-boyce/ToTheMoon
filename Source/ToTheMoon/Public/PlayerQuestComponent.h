// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerQuestComponent.generated.h"

class UQuestBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOTHEMOON_API UPlayerQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerQuestComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	///Quests ----------------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player|Quests")
	TArray<TSubclassOf<UQuestBase>> TESTQUEUE;
	
	TQueue<TSubclassOf<UQuestBase>> QuestQueue;

	UFUNCTION()
	void HandleStepCompleted();
		
};
