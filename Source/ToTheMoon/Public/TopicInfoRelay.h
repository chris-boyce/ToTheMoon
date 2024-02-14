// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "QuestionData.h"
#include "Components/ActorComponent.h"
#include "TopicInfoRelay.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOTHEMOON_API UTopicInfoRelay : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTopicInfoRelay();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FString GatherTopicInfo(FQuestionTopic QuestionTopic);

	FString SearchMission();

	FString SearchPlanet();

	FString SearchTime();

	FString SearchThreats();

	FString SearchOtherPlanets();

		
};
