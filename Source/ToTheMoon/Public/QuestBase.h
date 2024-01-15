// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestBase.generated.h"

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
	NotStarted,
	InProgress,
	Completed,
	Failed
};

USTRUCT(BlueprintType)
struct FQuestStep
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StepDescription;
	
};


UCLASS()
class TOTHEMOON_API UQuestBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestStep> QuestSteps;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EQuestStatus QuestStatus;

	UFUNCTION(BlueprintCallable)
	void StartQuest();

	UFUNCTION(BlueprintCallable)
	void CompleteStep(int32 StepIndex);
};
