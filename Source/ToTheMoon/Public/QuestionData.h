// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "QuestionData.generated.h"
UENUM(BlueprintType)
enum class FQuestionTopic : uint8
{
	Null, Mission, PlanetInfo, TimeInfo, ThreatInfo, OtherPlanetInfo
};


USTRUCT(BlueprintType)
struct FQuestions : public FTableRowBase
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere)
	FString DisplayQuestion;

	UPROPERTY(EditAnywhere)
	FString InputQuestion;

	UPROPERTY(EditAnywhere)
	FQuestionTopic Topic;
};


