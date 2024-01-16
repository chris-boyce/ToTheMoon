// Semester 2 Christopher Boyce : TTM Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStepCompleted);


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
	FString QuestDescription;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EQuestStatus QuestStatus;

	UFUNCTION(BlueprintCallable)
	virtual void StartQuest();
	
	UFUNCTION(BlueprintCallable)
	void CompleteStep();

	UPROPERTY()
	FStepCompleted StepCompleted;

	
};
